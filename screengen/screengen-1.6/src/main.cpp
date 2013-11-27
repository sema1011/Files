#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QTextCodec>
#include <QTranslator>
#include <QFileInfo>
#include <QSettings>
#include "qffmpeg.h"
#include "qshadow.h"

QColor getColorFromString (QString tc);
int fontWeightFromString (QString w, int def);

int main(int argc, char *argv[]){
	QApplication app(argc, argv, false);
	QTextCodec *codec = QTextCodec::codecForName("UTF8");
	QTextCodec::setCodecForCStrings(codec);
	QTranslator translator;
	translator.load ("screengen_"+QLocale::system().name()+".qm","/usr/share/screengen/translations/");
	app.installTranslator (&translator);

	qDebug()<<"Screenlist generator from video file. Version 1.6. Copyright (C) 2012 Oleg Kochkin. License - GPL.";
// Видеофайл
	QString videoFile = "";
// Секция предустановок
	QString preset="Default";
	for (int i=1;i<argc;i++) if (QString(argv[i]) == "--preset") preset=argv[i+1];

	QSettings cfg("screengen","screengen");
	cfg.beginGroup(preset);
	
	bool presetsList=false;
	QString presetInfo="";

	int frames=cfg.value ("frames",16).toInt();// Всего кадров
	int widthList=cfg.value ("width",1200).toInt();// Ширина листа
	int horCount=cfg.value ("horCount",4).toInt();// Количество кадров по горизонтали в листе
	QString offsetBegin=cfg.value ("offsetBegin","00:01:00").toString();// Время начала
	QString offsetEnd=cfg.value ("offsetEnd","00:01:00").toString();// Время окончания
	int listBorder=cfg.value ("listBorder",10).toInt();// Толщина бордюра листа
	int frameBorder=cfg.value ("frameBorder",5).toInt();// Толщина бордюра кадра
	int shadowOffset=cfg.value ("shadowOffset",5).toInt();// Смещение тени от кадра
	int shadowInt=cfg.value ("shadowInt",10).toInt();// Интенсивность тени (0-100)
	QString shadowColor=cfg.value ("shadowColor","0,0,0").toString();// Цвет тени
	QString background=cfg.value ("background","").toString();// Файл фона
	QString backgroundColor=cfg.value ("backgroundColor","255,255,255").toString();// Цвет фона
	QString picType=cfg.value ("picType","jpg").toString();// Тип выходной картинки
	bool header=cfg.value ("header",true).toBool();// Заголовок
	bool timeFrame=cfg.value ("timeFrame",true).toBool();// Время в кадре
	QString fontFrameName=cfg.value ("fontFrameName","Liberation Sans").toString();// Имя шрифта в кадре
	int fontFrameSize=cfg.value ("fontFrameSize",10).toInt();// Размер шрифта в кадре
	int fontFrameWeight = QFont::Normal;// Тип шрифта в кадре
	QString fontFrameWeightS=cfg.value ("fontFrameWeight","Normal").toString();
	bool fontFrameItalic=cfg.value ("fontFrameItalic",false).toBool();// Шрифт Italic в кадре
	QString fontFrameColor=cfg.value ("fontFrameColor","255,255,255").toString();// Цвет шрифта в кадре
	int fontFrameShadowOffset=cfg.value ("fontFrameShadowOffset",0).toInt();// Смещение тени от штампа времени
	int fontFrameShadowInt=cfg.value ("fontFrameShadowInt",2).toInt();// Интенсивность тени от штампа времени
	QString fontFrameShadowColor=cfg.value ("fontFrameShadowColor","0,0,0").toString();// Цвет тени от штампа времени
	QString fontHeaderName=cfg.value ("fontHeaderName","Liberation Sans").toString();// Имя шрифта в заголовке
	int fontHeaderSize=cfg.value ("fontHeaderSize",13).toInt();// Размер шрифта в заголовке
	int fontHeaderWeight = QFont::Bold;// Тип шрифта в заголовке
	QString fontHeaderWeightS=cfg.value ("fontHeaderWeight","Bold").toString();
	bool fontHeaderItalic=cfg.value ("fontHeaderItalic",false).toBool();// Шрифт Italic в заголовке
	QString fontHeaderColor=cfg.value ("fontHeaderColor","0,0,0").toString();// Цвет шрифта в заголовке
	QString headerBackground=cfg.value ("headerBackground","").toString();// Файл для заднего плана заголовка
	QString headerColor=cfg.value ("headerColor","255,255,255").toString();// Цвет фона заголовка
	QString headerBorderColor=cfg.value ("headerBorderColor","0,0,0").toString();// Цвет бордюра заголовка
	int headerBorder=cfg.value ("headerBorder",2).toInt();// Толщина бордюра заголовка
	QString foreground=cfg.value ("foreground","").toString();// Файл водяного знака
	double aspect=cfg.value ("aspect",0.0).toDouble();// Соотношение сторон кадра
	int textFlag = Qt::AlignRight | Qt::AlignBottom;// Позиция времени в кадре
	QString stampPos=cfg.value ("stampPos","rb").toString();
	int infoShadowOffset=cfg.value ("infoShadowOffset",5).toInt();// Смещение тени для текста информации
	int infoShadowInt=cfg.value ("infoShadowInt",10).toInt();// Интенсивность тени (0-100) для текста информации
	QString infoShadowColor=cfg.value ("infoShadowColor","100,100,100").toString();// Цвет тени для текста информации
	QString logoFile=cfg.value ("logoFile","").toString();// Файл логотипа
	int logoShadowOffset=cfg.value ("logoShadowOffset",5).toInt();// Смещение тени для логотипа
	int logoShadowInt=cfg.value ("logoShadowInt",10).toInt();// Интенсивность тени (0-100) для логотипа
	QString logoShadowColor=cfg.value ("logoShadowColor","100,100,100").toString();// Цвет тени для логотипа
	QString descr=cfg.value ("descr","").toString();// Комментарий
	int stampOffset=cfg.value ("stampOffset",3).toInt();// Отступ штампа времени от края кадра
	QString outFolder=cfg.value ("outFolder","").toString();// Папка для картинок
	QString frameBoxColor=cfg.value ("frameBoxColor","120,120,120").toString();// Цвет бордюра кадра
	int frameBox=cfg.value ("frameBox",0).toInt();// Толщина бордюра кадра
	int textDescrFlag = Qt::AlignLeft | Qt::AlignTop;// Позиция текста в кадре
	QString stampDescrPos=cfg.value ("stampDescrPos","lt").toString();
	QString stampDescr=cfg.value ("stampDescr","").toString();// Комментарий
	
	cfg.setValue ("frames",frames);
	cfg.setValue ("width",widthList);
	cfg.setValue ("horCount",horCount);
	cfg.setValue ("offsetBegin",offsetBegin);
	cfg.setValue ("offsetEnd",offsetEnd);
	cfg.setValue ("listBorder",listBorder);
	cfg.setValue ("frameBorder",frameBorder);
	cfg.setValue ("shadowOffset",shadowOffset);
	cfg.setValue ("shadowInt",shadowInt);
	cfg.setValue ("shadowColor",shadowColor);
	cfg.setValue ("background",background);
	cfg.setValue ("backgroundColor",backgroundColor);
	cfg.setValue ("picType",picType);
	cfg.setValue ("header",header);
	cfg.setValue ("timeFrame",timeFrame);
	cfg.setValue ("fontFrameName",fontFrameName);
	cfg.setValue ("fontFrameSize",fontFrameSize);
	cfg.setValue ("fontFrameWeight",fontFrameWeightS);
	cfg.setValue ("fontFrameItalic",fontFrameItalic);
	cfg.setValue ("fontFrameColor",fontFrameColor);
	cfg.setValue ("fontHeaderName",fontHeaderName);
	cfg.setValue ("fontHeaderSize",fontHeaderSize);
	cfg.setValue ("fontHeaderWeight",fontHeaderWeightS);
	cfg.setValue ("fontHeaderItalic",fontHeaderItalic);
	cfg.setValue ("fontHeaderColor",fontHeaderColor);
	cfg.setValue ("headerBackground",headerBackground);
	cfg.setValue ("headerColor",headerColor);
	cfg.setValue ("headerBorderColor",headerBorderColor);
	cfg.setValue ("headerBorder",headerBorder);
	cfg.setValue ("foreground",foreground);
	cfg.setValue ("aspect",aspect);
	cfg.setValue ("stampPos",stampPos);
	cfg.setValue ("infoShadowOffset",infoShadowOffset);
	cfg.setValue ("infoShadowInt",infoShadowInt);
	cfg.setValue ("infoShadowColor",infoShadowColor);
	cfg.setValue ("logoFile",logoFile);
	cfg.setValue ("logoShadowOffset",logoShadowOffset);
	cfg.setValue ("logoShadowInt",logoShadowInt);
	cfg.setValue ("logoShadowColor",logoShadowColor);
	cfg.setValue ("descr",descr);
	cfg.setValue ("stampOffset",stampOffset);
	cfg.setValue ("outFolder",outFolder);
	cfg.setValue ("fontFrameShadowOffset",fontFrameShadowOffset);
	cfg.setValue ("fontFrameShadowInt",fontFrameShadowInt);
	cfg.setValue ("fontFrameShadowColor",fontFrameShadowColor);
	cfg.setValue ("frameBoxColor",frameBoxColor);
	cfg.setValue ("frameBox",frameBox);
	cfg.setValue ("stampDescrPos",stampDescrPos);
	cfg.setValue ("stampDescr",stampDescr);
	cfg.endGroup();
		
	videoFile = argv[1];
	for (int i=1;i<argc;i++){
	if (QString(argv[i]) == "--frames") frames=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--width") widthList=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--horCount") horCount=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--offsetBegin") offsetBegin=QString(argv[i+1]);
	if (QString(argv[i]) == "--offsetEnd") offsetEnd=QString(argv[i+1]);
	if (QString(argv[i]) == "--listBorder") listBorder=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--frameBorder") frameBorder=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--shadowOffset") shadowOffset=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--shadowInt") shadowInt=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--shadowColor") shadowColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--background") background=QString(argv[i+1]);
	if (QString(argv[i]) == "--backgroundColor") backgroundColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--picType") picType=QString(argv[i+1]);
	if (QString(argv[i]) == "--fontFrameName") fontFrameName=QString(argv[i+1]);
	if (QString(argv[i]) == "--fontFrameSize") fontFrameSize=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--fontFrameColor") fontFrameColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--fontFrameShadowOffset") fontFrameShadowOffset=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--fontFrameShadowInt") fontFrameShadowInt=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--fontFrameShadowColor") fontFrameShadowColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--fontHeaderName") fontHeaderName=QString(argv[i+1]);
	if (QString(argv[i]) == "--fontHeaderSize") fontHeaderSize=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--fontHeaderColor") fontHeaderColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--headerBackground") headerBackground=QString(argv[i+1]);
	if (QString(argv[i]) == "--headerColor") headerColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--headerBorderColor") headerBorderColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--headerBorder") headerBorder=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--foreground") foreground=QString(argv[i+1]);
	if (QString(argv[i]) == "--infoShadowOffset") infoShadowOffset=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--infoShadowInt") infoShadowInt=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--infoShadowColor") infoShadowColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--logoFile") logoFile=QString(argv[i+1]);
	if (QString(argv[i]) == "--logoShadowOffset") logoShadowOffset=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--logoShadowInt") logoShadowInt=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--logoShadowColor") logoShadowColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--descr") descr=QString(argv[i+1]);
	if (QString(argv[i]) == "--stampOffset") stampOffset=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--outFolder") outFolder=QString(argv[i+1]);
	if (QString(argv[i]) == "--aspect") aspect=QString(argv[i+1]).toDouble();
	if (QString(argv[i]) == "--stampPos")	stampPos=QString(argv[i+1]);
	if (QString(argv[i]) == "--frameBoxColor") frameBoxColor=QString(argv[i+1]);
	if (QString(argv[i]) == "--frameBox") frameBox=QString(argv[i+1]).toInt();
	if (QString(argv[i]) == "--stampDescrPos")	stampDescrPos=QString(argv[i+1]);
	if (QString(argv[i]) == "--stampDescr")	stampDescr=QString(argv[i+1]);
	if (QString(argv[i]) == "--fontFrameWeight") QString fontFrameWeightS=QString(argv[i+1]);
	if (QString(argv[i]) == "--fontHeaderWeight") QString fontHeaderWeightS=QString(argv[i+1]);
	if (QString(argv[i]) == "--presetsList") presetsList=true;
	if (QString(argv[i]) == "--presetInfo") presetInfo=QString(argv[i+1]);

	if (QString(argv[i]) == "--header") {
		if (QString(argv[i+1]) == "true") header=true;
		else header=false;
		}
	if (QString(argv[i]) == "--timeFrame") {
		if (QString(argv[i+1]) == "true") timeFrame=true;
		else timeFrame=false;
		}
	if (QString(argv[i]) == "--fontFrameItalic") {
		if (QString(argv[i+1]) == "true") fontFrameItalic=true;
		else fontFrameItalic=false;
		}
	if (QString(argv[i]) == "--fontHeaderItalic") {
		if (QString(argv[i+1]) == "true") fontHeaderItalic=true;
		else fontHeaderItalic=false;
		}
	}

	if (presetsList){
		qDebug()<<"Presets in "<<cfg.fileName()<<":";
		QStringList presets = cfg.childGroups();
		foreach (QString preset, presets) qDebug()<<preset;
		return 0;
		}
		
	if (! presetInfo.isEmpty()){
		qDebug()<<"Values in preset"<<presetInfo<<"in file"<<cfg.fileName()<<":";
		cfg.beginGroup(presetInfo);
		QStringList preset = cfg.childKeys();
		foreach (QString key, preset){
			QString str = key+" = "+ cfg.value(key,"").toString();
			qDebug()<<str;
			}
		cfg.endGroup();
		return 0;
		}

	if (argc < 2){
		qDebug()<<"screengen videoFile [parameters]";
		qDebug()<<"Parameters:";
		qDebug()<<"   --preset                  Use section in config file (default - \"Default\")";
		qDebug()<<"   --presetsList             Show all presets in config file (all other parameters ignored)";
		qDebug()<<"   --presetInfo              Show all values in preset (all other parameters ignored, example: --presetInfo MyPreset";
		qDebug()<<"   --frames                  Frames count in screenlist (default - 16)";
		qDebug()<<"   --width                   Width screenlist (default - 1200)";
		qDebug()<<"   --horCount                Frames in horisontal (default - 4)";
		qDebug()<<"   --offsetBegin             Time offset from begin (default - \"00:01:00\")";
		qDebug()<<"   --offsetEnd               Time offset from end (default - \"00:01:00\")";
		qDebug()<<"   --listBorder              Depth border screenlist (default - 10)";
		qDebug()<<"   --frameBorder             Depth border frame (default - 5)";
		qDebug()<<"   --shadowOffset            Offset shadow of frame (default - 5)";
		qDebug()<<"   --shadowInt               Intensity shadow of frame (default - 10, range 0-100)";
		qDebug()<<"   --shadowColor             R,G,B color shadow of frame (default - \"0,0,0\" - black, \"255,255,255\" - white)";
		qDebug()<<"   --background              Picture file for background (if empty, fill white)";
		qDebug()<<"   --backgroundColor         R,G,B[,A] background color (default - \"255,255,255\")";
		qDebug()<<"   --picType                 Type of picture file (default - \"jpg\")";
		qDebug()<<"   --header                  Header with information (default - true)";
		qDebug()<<"   --timeFrame               Time stamp on frame (default - true)";
		qDebug()<<"   --fontFrameName           Name font on frame (default - \"Liberation Sans\")";
		qDebug()<<"   --fontFrameSize           Size font on frame (default - 10)";
		qDebug()<<"   --fontFrameWeight         Weight font on frame (default - Normal, (Light,DemiBold,Bold,Black))";
		qDebug()<<"   --fontFrameItalic         Italic font on frame (default - false)";
		qDebug()<<"   --fontFrameColor          R,G,B[,A] color font on frame (default - \"255,255,255\")";
		qDebug()<<"   --fontFrameShadowOffset   Offset shadow of time stamp (default - 0)";
		qDebug()<<"   --fontFrameShadowInt      Intensity shadow of time stamp (default - 2, range 0-100)";
		qDebug()<<"   --fontFrameShadowColor    R,G,B color shadow of time stamp (default - \"0,0,0\")";
		qDebug()<<"   --stampPos                Position time stamp (default - \"rb\" (RightBottom), (rb, rt, lb, lr))";
		qDebug()<<"   --stampOffset             Offset from the edge of the frame to the timestamp (default - 3)";
		qDebug()<<"   --fontHeaderName          Name font on header (default - \"Liberation Sans\")";
		qDebug()<<"   --fontHeaderSize          Size font on header (default - 13)";
		qDebug()<<"   --fontHeaderWeight        Weight font on header (default - Bold, (Normal,Light,DemiBold,Black))";
		qDebug()<<"   --fontHeaderItalic        Italic font on header (default - false)";
		qDebug()<<"   --fontHeaderColor         R,G,B[,A] color font on header (default - \"0,0,0\")";
		qDebug()<<"   --headerBackground        Picture file for header background (if empty, default color for header)";
		qDebug()<<"   --headerColor             R,G,B[,A] color header background (default - \"255,255,255\")";
		qDebug()<<"   --headerBorderColor       R,G,B[,A] color header border (default - \"0,0,0\")";
		qDebug()<<"   --headerBorder            Depth border header (default - 2)";
		qDebug()<<"   --infoShadowOffset        Offset shadow of information text (default - 5)";
		qDebug()<<"   --infoShadowInt           Intensity shadow of information text (default - 10, range 0-100)";
		qDebug()<<"   --infoShadowColor         R,G,B color shadow of information text (default - \"100,100,100\")";
		qDebug()<<"   --logoFile                Picture file for logotype (it is recommended PNG image with alpha channel)";
		qDebug()<<"   --logoShadowOffset        Offset shadow of logotype (default - 5)";
		qDebug()<<"   --logoShadowInt           Intensity shadow of logotype (default - 10, range 0-100)";
		qDebug()<<"   --logoShadowColor         R,G,B color shadow of logotype (default - \"100,100,100\")";
		qDebug()<<"   --foreground              Picture file for foreground (it is recommended PNG image with alpha channel)";
		qDebug()<<"   --aspect                  Aspect ratio (if 0.0 - source aspect, default - 0.0)";
		qDebug()<<"   --descr                   Custom text, located at the top of the header";
		qDebug()<<"   --outFolder               Folder for result files";
		qDebug()<<"   --frameBoxColor           R,G,B[,A] color frame border (default - \"120,120,120\")";
		qDebug()<<"   --frameBox                Depth border frame (default - 0)";
		qDebug()<<"   --stampDescr              Custom text, located on frame";
		qDebug()<<"   --stampDescrPos           Position custom text (default - \"lt\" (LeftTop), (rb, rt, lb, lr))";
		return 4;
		}

	fontFrameWeight = fontWeightFromString (fontFrameWeightS, QFont::Normal);
	fontHeaderWeight = fontWeightFromString (fontHeaderWeightS, QFont::Bold);

	if (stampPos == "rb") textFlag = Qt::AlignRight | Qt::AlignBottom;
	if (stampPos == "rt") textFlag = Qt::AlignRight | Qt::AlignTop;
	if (stampPos == "lb") textFlag = Qt::AlignLeft | Qt::AlignBottom;
	if (stampPos == "lt") textFlag = Qt::AlignLeft | Qt::AlignTop;
	
	if (stampDescrPos == "rb") textDescrFlag = Qt::AlignRight | Qt::AlignBottom;
	if (stampDescrPos == "rt") textDescrFlag = Qt::AlignRight | Qt::AlignTop;
	if (stampDescrPos == "lb") textDescrFlag = Qt::AlignLeft | Qt::AlignBottom;
	if (stampDescrPos == "lt") textDescrFlag = Qt::AlignLeft | Qt::AlignTop;

	QString outFile = videoFile+"."+picType;

	if (videoFile.isEmpty()) return 3;
	if (shadowInt<0) shadowInt=0;
	if (shadowInt>100) shadowInt=100;
	
	TFfmpeg *video = new TFfmpeg(videoFile);

// Ширина листа, исключая бордюр
	int wList = widthList - listBorder * 2;
// Ширина кадра в листе
	int widthFrame = wList / horCount;
// Количество кадров по вертикали в листе
	int vertCount = frames / horCount;
// Ширина кадра в видеофайле
	int wFrame = video->vWidth;
// Высота кадра в видеофайле
	int hFrame = video->vHeight;
// Коэффициент уменьшения (соотношение ширины/высоты кадра в видеофайле к ширине/высоте кадра в листе)
	double koeff = (double) wFrame / widthFrame;
// Высота кадра в листе
	int heightFrame = hFrame / koeff;
	if (aspect < -0.001 || aspect > 0.001) heightFrame = (double) widthFrame / aspect;
// Высота листа		
	int hList = heightFrame * vertCount + listBorder * 2;
		
	QFont headerFont (fontHeaderName, fontHeaderSize, fontHeaderWeight, fontHeaderItalic);
	QFontMetrics fm (headerFont);
	int fullLength = 	video->iDuration / 1000;
	int headerH=(fontHeaderSize+(double)5)*5;
	int headerX=listBorder+frameBorder;

	if (! descr.isEmpty()) headerH=(fontHeaderSize+(double)5)*7;

	if (! header) headerH=0;
	QImage imList (wList+listBorder*2, hList+headerH+frameBorder*2, QImage::Format_ARGB32_Premultiplied);
	imList.fill (getColorFromString(backgroundColor));

// Формирование тени для кадра
	QImage imFrameShadowSource (widthFrame-frameBorder*2, heightFrame-frameBorder*2, QImage::Format_ARGB32);
	imFrameShadowSource.fill ("black");
	QImage imFrameShadow = getShadow (imFrameShadowSource, shadowInt, getColorFromString (shadowColor));
	QPainter pList (&imList);
	if (! background.isEmpty()) pList.drawImage(QRectF (0,0,imList.width(),imList.height()),QImage (background));

// Заголовок
	if (header){
		int headerW=widthFrame*horCount-frameBorder*2;
		int headerY=listBorder+frameBorder;

		pList.setPen (QColor(0,0,0,0));
		QImage shadowHs (headerW, headerH, QImage::Format_ARGB32);
		shadowHs.fill ("black");
		QImage shadowHeader = getShadow (shadowHs, shadowInt, getColorFromString (shadowColor));
		pList.drawImage (QPoint ((headerX+shadowOffset)-shadowInt, (headerY+shadowOffset)-shadowInt),shadowHeader);
		if (headerBackground.isEmpty()) pList.setBrush (getColorFromString (headerColor));
		else pList.setBrush (QColor (0,0,0,0));
		if (headerBorder > 0) pList.setPen (QPen (getColorFromString (headerBorderColor), headerBorder));
		else pList.setPen (QPen (QColor (0,0,0,0), headerBorder));
		pList.drawRect (headerX, headerY, headerW, headerH);
		if (! headerBackground.isEmpty()) pList.drawImage (QRect (headerX, headerY, headerW, headerH), QImage (headerBackground));
		pList.setPen (QPen (getColorFromString (fontHeaderColor),2.0));
		pList.setFont (QFont (fontHeaderName, fontHeaderSize, fontHeaderWeight, fontHeaderItalic));

		QString fileName = QFileInfo(videoFile).fileName();
		QString fileSize = QString::number(QFileInfo(videoFile).size() / 1048576) + " " + QObject::tr("Mb");
		QString generalInfo = video->generalInfo;
		QString videoInfo = video->getVInfo();
		QString audioInfo = video->getAInfo();

		int step=fontHeaderSize+1, num=1, offs=8;
		int dx = fontHeaderSize*10;
		
		QImage imText (imList.width()-(listBorder*2+frameBorder*2),headerH, QImage::Format_ARGB32);
		imText.fill(0);
		QPainter pText(&imText);
		pText.setFont (headerFont);
		QPen tPen (getColorFromString(fontHeaderColor));
		tPen.setWidth (fontHeaderSize / 6);
		pText.setPen (tPen);
		if (! descr.isEmpty()){
			pText.drawText (10, num*step+offs, descr);
			pText.drawLine (10, step+offs*2, fm.width(descr)+20, step+offs*2);
			num+=2;
			}
		pText.drawText(10,num*step+offs,QObject::tr("File name:"));
		pText.drawText(dx,num*step+offs,fileName);num++;
		pText.drawText(10,num*step+offs,QObject::tr("Size:"));
		pText.drawText(dx,num*step+offs,fileSize);num++;
		pText.drawText(10,num*step+offs,QObject::tr("General info:"));
		pText.drawText(dx,num*step+offs,generalInfo);num++;
		pText.drawText(10,num*step+offs,QObject::tr("Video:"));
		pText.drawText(dx,num*step+offs,videoInfo);num++;
		pText.drawText(10,num*step+offs,QObject::tr("Audio:"));
		pText.drawText(dx,num*step+offs,audioInfo);
		pText.end();
		QImage imTextS = getShadow (imText, infoShadowInt, getColorFromString (infoShadowColor));
		pList.drawImage ((listBorder+frameBorder+infoShadowOffset)-infoShadowInt, (listBorder+infoShadowOffset+frameBorder)-infoShadowInt, imTextS);
		pList.drawImage (listBorder+frameBorder, listBorder+frameBorder, imText);

// Логотип
		if (! logoFile.isEmpty()){
			QImage imLogo(logoFile);
			double imLogoAspect = (double) imLogo.width() / imLogo.height();
			int imLogoH = shadowHs.height()-20;
			int imLogoW = imLogoH * imLogoAspect;
			QImage imLogoScaled = imLogo.scaled(imLogoW,imLogoH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			QImage imLogoS = getShadow(imLogoScaled,logoShadowInt,getColorFromString(logoShadowColor));
			pList.drawImage (imList.width()-(listBorder+frameBorder+imLogoW+logoShadowInt+10)+logoShadowOffset, listBorder+frameBorder+10+logoShadowOffset-logoShadowInt, imLogoS);
			pList.drawImage (imList.width()-(listBorder+frameBorder+imLogoW+10), listBorder+frameBorder+10, imLogoScaled);
			}
		}
		
// Кадры
	int numFrame=0;
	QTime timeBeginT;
	QTime timeEndT;
	int timeBegin = timeBeginT.msecsTo(QTime::fromString(offsetBegin,"hh:mm:ss"));
	int timeEnd = timeEndT.msecsTo(QTime::fromString(offsetEnd,"hh:mm:ss"));
	int length = fullLength - (timeBegin+timeEnd);
	for (int vi = 0;vi < vertCount;vi++){
		for (int hi = 0;hi < horCount;hi++){
			int pos = length / (frames-1) * numFrame + timeBegin;
			QImage imFrameSource = video->getImage (pos);
			QImage imFrame = imFrameSource.scaled (widthFrame-frameBorder*2, heightFrame-frameBorder*2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			if (timeFrame){
				QImage imStamp (imFrame.width()-stampOffset*2, imFrame.height()-stampOffset*2, QImage::Format_ARGB32_Premultiplied);
				imStamp.fill(0);
				QPainter pStamp(&imStamp);
				pStamp.setPen (getColorFromString (fontFrameColor));
				pStamp.setFont (QFont (fontFrameName, fontFrameSize, fontFrameWeight, fontFrameItalic));
				pStamp.drawText (imStamp.rect(), textFlag, QTime(0,0,0,0).addMSecs(pos).toString("hh:mm:ss"));
				pStamp.end();
				QPainter pFrame(&imFrame);
				QImage imStampShadow = getShadow (imStamp, fontFrameShadowInt, getColorFromString (fontFrameShadowColor));
				pFrame.drawImage (stampOffset-fontFrameShadowInt, stampOffset-fontFrameShadowInt, imStampShadow);
				pFrame.drawImage (stampOffset, stampOffset, imStamp);
				pFrame.end();
				}

			if (! stampDescr.isEmpty()){
				QImage imStamp (imFrame.width()-stampOffset*2, imFrame.height()-stampOffset*2, QImage::Format_ARGB32_Premultiplied);
				imStamp.fill(0);
				QPainter pStamp(&imStamp);
				pStamp.setPen (getColorFromString (fontFrameColor));
				pStamp.setFont (QFont (fontFrameName, fontFrameSize, fontFrameWeight, fontFrameItalic));
				pStamp.drawText (imStamp.rect(), textDescrFlag, stampDescr);
				pStamp.end();
				QPainter pFrame(&imFrame);
				QImage imStampShadow = getShadow (imStamp, fontFrameShadowInt, getColorFromString (fontFrameShadowColor));
				pFrame.drawImage (stampOffset-fontFrameShadowInt, stampOffset-fontFrameShadowInt, imStampShadow);
				pFrame.drawImage (stampOffset, stampOffset, imStamp);
				pFrame.end();
				}

			int cX=hi*widthFrame+headerX;
			int cY=vi*heightFrame+listBorder+frameBorder*3+headerH;
			pList.drawImage (cX+shadowOffset-shadowInt, (vi*heightFrame+headerH+listBorder+shadowOffset+frameBorder*3)-shadowInt, imFrameShadow);
			pList.drawImage (cX, cY, imFrame);
			if (frameBox > 0){
				pList.setPen (QPen (getColorFromString (frameBoxColor), frameBox));
				pList.setBrush (QColor (0,0,0,0));
				pList.drawRect (cX, cY, widthFrame-frameBorder*2, heightFrame-frameBorder*2);
				}
			numFrame++;
			}
		}
	if (! foreground.isEmpty()) pList.drawImage (QRectF (0,0,wList+listBorder*2, hList+headerH), QImage (foreground));
	pList.end();
	QString outputFile=QFileInfo(outFile.toUtf8()).fileName();
	if (outFolder != "") outputFile=outFolder+"/"+QFileInfo(outFile.toUtf8()).fileName();
	if (! imList.save(outputFile)) qDebug()<<"Error save file.";
	qDebug()<<"Done.";
	return 0;
}

// Получение цвета из строки "R,G,B[,A]" -> QColor
QColor getColorFromString (QString tc) {
	QColor retColor ("red");
	if (tc.split(",").length() == 3) retColor = QColor (tc.split(",")[0].toInt(),tc.split(",")[1].toInt(),tc.split(",")[2].toInt());
	if (tc.split(",").length() == 4) retColor = QColor (tc.split(",")[0].toInt(),tc.split(",")[1].toInt(),tc.split(",")[2].toInt(),tc.split(",")[3].toInt());
	return retColor;
}

int fontWeightFromString (QString w, int def){
	int f=def;
	if (w == "Normal") f=QFont::Normal;
	if (w == "Light") f=QFont::Light;
	if (w == "DemiBold") f=QFont::DemiBold;
	if (w == "Bold") f=QFont::Bold;
	if (w == "Black") f=QFont::Black;
	return f;
}
