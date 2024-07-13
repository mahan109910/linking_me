// snowanimation.cpp
#include "snowanimation.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

SnowAnimation::SnowAnimation()
{
    setFlag(ItemHasNoContents, true); // این اجازه می‌دهد که QGraphicsItem شامل محتوایی باشد.
}

QRectF SnowAnimation::boundingRect() const
{
    return QRectF(0, 0, 100, 100); // اندازه محدوده برف را تعیین می‌کند.
}

void SnowAnimation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::white); // رنگ برف را تعیین می‌کند.
    painter->drawEllipse(boundingRect()); // یک دایره (برف) را رسم می‌کند.
}

void SnowAnimation::advance(int phase)
{
    if (phase == 0)
        return;

    // حرکت برف را اینجا پیاده‌سازی می‌کنیم (بر اساس محدوده boundingRect).
    setPos(x(), y() + 2); // حرکت برف به سمت پایین با سرعت 2 پیکسل در هر بار فراخوانی

    // اگر برف خارج از محدوده‌ی ارتفاع صحنه رفت، آن را به بالای صفحه باز می‌گردانیم.
    if (y() > scene()->height())
        setPos(x(), -boundingRect().height()); // تنظیم موقعیت برف برای شروع از بالا

    // این بخش را می‌توانید بر اساس نیاز خود تغییر دهید تا سرعت و حرکت برف دلخواه شما را پیاده‌سازی کنید.
}

