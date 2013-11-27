#include "qffmpeg.h"

// Открывает видеофайл, инициализирует кодеки, получает информацию о потоках
TFfmpeg::TFfmpeg(QString videoFile){
	av_log_set_level(AV_LOG_QUIET);
	avcodec_register_all();
	av_register_all();

	pAVFormatContext = avformat_alloc_context();
	if (avformat_open_input (&pAVFormatContext, videoFile.toLocal8Bit(), NULL, NULL)!=0) qDebug()<<"Error open file:"<<videoFile;
	else if (avformat_find_stream_info (pAVFormatContext, NULL) < 0) qDebug()<<"Not found streams in"<<videoFile;
	duration = QTime(0,0,0,0).addMSecs (pAVFormatContext->duration / 1000).toString("hh:mm:ss");
	fullBitrate = QString::number (pAVFormatContext->bit_rate / 1000);
	streamsCount = pAVFormatContext->nb_streams;
	generalInfo = duration+", "+QObject::tr("Streams:")+" "+QString::number (streamsCount)+", "+QObject::tr("Full bitrate:")+" "+fullBitrate+" "+QObject::tr("kb/s");

	vStreamNumber=-1;
	for (uint i=0; i < pAVFormatContext->nb_streams;i++)
		if (pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
			vStreamNumber=i;
			break;
			}
	if (vStreamNumber == -1) qDebug()<<"Not video stream in"<<videoFile;

	vCodecContext = pAVFormatContext->streams[vStreamNumber]->codec;
	vCodec = avcodec_find_decoder (vCodecContext->codec_id);
	if (avcodec_open2 (vCodecContext, vCodec, NULL)) qDebug()<<"Not open video codec in"<<videoFile;

	vResolution = QString::number (vCodecContext->width) + "x" + QString::number (vCodecContext->height);
	vFps = QString::number ((double) pAVFormatContext->streams[vStreamNumber]->r_frame_rate.num / pAVFormatContext->streams[vStreamNumber]->r_frame_rate.den);
	vCodecName = QString(vCodec->name).toUpper();
	vWidth = vCodecContext->width;
	vHeight = vCodecContext->height;
	iDuration = pAVFormatContext->duration;
	
	aStreamNumber=-1;
	for (uint i=0; i < pAVFormatContext->nb_streams;i++)
		if (pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO){
			aStreamNumber=i;
			break;
			}
	if (aStreamNumber == -1) qDebug()<<"Not audio stream in"<<videoFile;
	else{
		aCodecContext = pAVFormatContext->streams[aStreamNumber]->codec;
		aCodec = avcodec_find_decoder (aCodecContext->codec_id);
		if (avcodec_open2 (aCodecContext, aCodec, NULL)) qDebug()<<"Not open audio codec in"<<videoFile;
		}

	if (vCodecContext->codec_tag > 0){
		char vCodecTagC[32];
		av_get_codec_tag_string (vCodecTagC, sizeof(vCodecTagC), vCodecContext->codec_tag);
		vCodecTag = QString (vCodecTagC);
		}

	char aChC[32];
	if (aStreamNumber != -1){
		av_get_channel_layout_string (aChC, sizeof(aChC), aCodecContext->channels, aCodecContext->channel_layout);
		aChannels = QString (aChC);
		aSamples = QString::number ((double)aCodecContext->sample_rate / 1000);
		aBitrate = QString::number (get_bit_rate (aCodecContext)/1000);
		aCodecName = QString(aCodec->name).toUpper();
		}
	}

// Вычисляет битрейт потока (пока только для звука, и то, не всегда)
int TFfmpeg::get_bit_rate(AVCodecContext *ctx){
	int bit_rate;
	int bits_per_sample;

	switch(ctx->codec_type) {
		case AVMEDIA_TYPE_VIDEO:
		case AVMEDIA_TYPE_DATA:
		case AVMEDIA_TYPE_SUBTITLE:
		case AVMEDIA_TYPE_ATTACHMENT:
			bit_rate = ctx->bit_rate;
				break;
		case AVMEDIA_TYPE_AUDIO:
			bits_per_sample = av_get_bits_per_sample(ctx->codec_id);
			bit_rate = bits_per_sample ? ctx->sample_rate * ctx->channels * bits_per_sample : ctx->bit_rate;
				break;
		default:
			bit_rate = 0;
				break;
		}
	return bit_rate;
}

// Получение строки с информацией о видео потоке
QString TFfmpeg::getVInfo(){
	QString vct = ", ";
	if ((vCodecContext->codec_tag > 0) && (vCodecTag != vCodecName)) vct = " ("+vCodecTag+"), ";
	return vCodecName + vct + vResolution + ", " + vFps + " " + QObject::tr("fps");
}

// Получение строки с информацией об аудио потоке
QString TFfmpeg::getAInfo(){
	QString ret="";
	if (aStreamNumber != -1){
		QString br = "";
		if (aBitrate != "0") br = ", " + aBitrate + " " + QObject::tr("kb/s");
		ret = aCodecName + ", " + aChannels.toUpper() + ", " + aSamples + " " + QObject::tr("kHz") + br;
		}
	else ret = QObject::tr("Not present");
	return ret;
	}

// Закрытие видеофайла
TFfmpeg::~TFfmpeg(){
	avformat_close_input (&pAVFormatContext);
}

// Получение картинки в QImage кадра из видеофайла в позиции ms миллисекунд
QImage TFfmpeg::getImage(uint ms){
	QImage img = QImage(vCodecContext->width, vCodecContext->height, QImage::Format_RGB888);
	AVFrame *pFrame, *pFrameRGB;
	AVPacket packet;
	int numBytes;
	uint8_t *buffer;
	int frameFinished;

	pFrame = avcodec_alloc_frame();
	pFrameRGB = avcodec_alloc_frame();

	numBytes = avpicture_get_size (PIX_FMT_RGB24, vCodecContext->width, vCodecContext->height);
	buffer = (uint8_t *) av_malloc (numBytes * sizeof(uint8_t));
	avpicture_fill ((AVPicture *) pFrameRGB, buffer, PIX_FMT_RGB24,	vCodecContext->width, vCodecContext->height);

	int frameNum = av_rescale (ms,pAVFormatContext->streams[vStreamNumber]->time_base.den, pAVFormatContext->streams[vStreamNumber]->time_base.num) / 1000;
	avformat_seek_file (pAVFormatContext, vStreamNumber, 0, frameNum, frameNum, AVSEEK_FLAG_FRAME);
	avcodec_flush_buffers (vCodecContext);

	while (av_read_frame (pAVFormatContext, &packet) >= 0){
		if (packet.stream_index == vStreamNumber){
			avcodec_decode_video2 (vCodecContext, pFrame, &frameFinished, &packet);
			if (frameFinished){
				struct SwsContext *context;
				context = sws_getContext (vCodecContext->width, vCodecContext->height, vCodecContext->pix_fmt, vCodecContext->width,vCodecContext->height, PIX_FMT_RGB24, SWS_BICUBIC, 0, 0, 0);
				sws_scale (context, (uint8_t**) pFrame->data, pFrame->linesize, 0, vCodecContext->height, pFrameRGB->data, pFrameRGB->linesize);
				for (int j=0; j<vCodecContext->height; j++) memcpy (img.scanLine (j), pFrameRGB->data[0] + j * pFrameRGB->linesize[0], vCodecContext->width * 3);
				break;
				}
			}
		av_free_packet (&packet);
		}
	return img;
}
