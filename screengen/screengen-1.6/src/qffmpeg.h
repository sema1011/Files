#define __STDC_CONSTANT_MACROS

#include <QString>
#include <QImage>
#include <QDebug>
#include <QTime>

extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/mathematics.h>	// Added for Kubuntu (patch from srog (qt-apps.org))
  }

class TFfmpeg{
public:
	TFfmpeg(QString videoFile);
	~TFfmpeg();
	int get_bit_rate(AVCodecContext *ctx);
	QString getVInfo();
	QString getAInfo();
	QImage getImage(uint ms);
	
	int vStreamNumber, aStreamNumber, streamsCount, vWidth, vHeight;
	int64_t iDuration;
	QString vCodecTag, aChannels, aSamples, vResolution, vFps, aBitrate, fullBitrate, vCodecName, aCodecName, duration, generalInfo;
private:
	AVCodecContext getVCodecContext();
	AVFormatContext *pAVFormatContext;
	AVCodecContext *vCodecContext, *aCodecContext;
	AVCodec *vCodec, *aCodec;
};
