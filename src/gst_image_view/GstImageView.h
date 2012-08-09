#ifndef GST_IMAGE_VIEW_H
#define GST_IMAGE_VIEW_H

#include <QtGui>
#include <QtCore>

#include <base/samples/frame.h>
#include <frame_helper/FrameQImageConverter.h>
#include "rock_widget_collection/progress_indicator/ProgressIndicator.h"

enum TextLocation
{
    TOPLEFT = 0,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT
};

class GstImageView : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("Author", "Allan Conquest")
    
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor)
    
    /** The time without frame update in ms after which the progress indicator gets started  */
    Q_PROPERTY(int progress_indicator_timeout READ getProgressIndicatorTimeout WRITE setProgressIndicatorTimeout)
    
    /* Properties for use with GStreamer. That means in particluar that any of 
     * the following properties is unimportant if useGst is set to false. */
    
    /** Text based GStreamer pipeline description */
    Q_PROPERTY(QString pipelineDescription READ getPipelineDescription WRITE setPipelineDescription)
    
    /** Use OpenGL. Makes only sense if your graphics hardware supports OpenGL. 
     * If set to false, software rendering is used instead. */
    Q_PROPERTY(bool useGl READ getUseGl WRITE setUseGl)
    
    
public:
    GstImageView(QWidget *parent = 0);
    virtual ~GstImageView();
    
public slots:
    const QColor& getBackgroundColor() const;
    void setBackgroundColor(const QColor & color);
    const QString getPipelineDescription() const;
    void setPipelineDescription(QString descr);
    const int getProgressIndicatorTimeout() const;
    void setProgressIndicatorTimeout(int timeout);
    bool getUseGl();
    void setUseGl(bool use_gl);
    
    /* Overlays */
    void addCircle(QPointF center, double radius, bool persistent = 0);
    void addLine(QLineF &line, bool persistent = 0);
    void addText(QString text, TextLocation location, bool persistent = 0);
    
    void clearOverlays(bool clear_persistent_items = 0);
    
    /**
     * Rotates the displayed image about deg degrees while keeping its aspect ratio.
     */
    void rotate(int deg);
    void saveImage(QString path = QString(), bool overlay = 0);
    
    /* Other slots */
    void setFrame(const base::samples::frame::Frame &frame);
    void update2();

protected:
    void resizeEvent(QResizeEvent *event);
    void contextMenuEvent ( QContextMenuEvent * event );

private slots:
    void rotate_clockwise();
    void rotate_counterclockwise();
    void rotate_180();
    void save_image();
    void save_image_overlay();
    
private:
    void addDrawItem(QGraphicsScene *scene, QGraphicsItem *item, bool persistent = 0);
    void setItemPositions();
    void setupContextMenu();
    
    QColor bgColor;
    QString pipelineDescription;
    int progress_indicator_timeout;
    bool use_gl;

    QGraphicsView *imageView;
    QGraphicsProxyWidget *imageViewProxy;
    QGraphicsScene *imageScene;
    QGraphicsView *fixedOverlayView;
    QGraphicsScene *fixedOverlayScene;
    QGraphicsPixmapItem *imageItem;
    QImage image;

    QList<QGraphicsItem*> persistentDrawItems;
    QList<QGraphicsItem*> volatileDrawItems;

    QSize imageSize;

    frame_helper::FrameQImageConverter frame_converter;
    
    ProgressIndicator *progress_indicator;
    QTimer *progress_indicator_timer;
    
    /* Menus and actions */
    QMenu *contextMenu;
    QAction *rotate_image_clockwise_act;
    QAction *rotate_image_counterclockwise_act;
    QAction *rotate_image_180_act;
    QAction *save_image_act;
    QAction *save_image_overlay_act;
};

#endif /* GST_IMAGE_VIEW_H */