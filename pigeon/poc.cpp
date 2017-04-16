#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>

void click(int x, int y) {
    CGEventRef down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown,
        CGPointMake(x, y),
        kCGMouseButtonLeft
    );

    CGEventRef up = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseUp,
        CGPointMake(x, y),
        kCGMouseButtonLeft
    );

    CGEventPost(kCGHIDEventTap, down);
    //sleep(1);
    CGEventPost(kCGHIDEventTap, up);

    CFRelease(up);
    CFRelease(down);
}

void move(int x, int y) {
    CGEventRef move = CGEventCreateMouseEvent(
        NULL, kCGEventMouseMoved,
        CGPointMake(x, y),
        kCGMouseButtonLeft // ignored
    );

    CGEventPost(kCGHIDEventTap, move);

    CFRelease(move);
}

int main() {
    click(60, 260);
    sleep(1);
    click(200, 472);
    sleep(1);
    click(60, 260);
    sleep(1);
    return 0;
}

