#define WIN32_LEAN_AND_MEAN
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <Windows.h>
#include <windowsx.h>

class RootWidget : public QWidget {
    Q_OBJECT

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override {
        MSG *msg = reinterpret_cast<MSG *>(message);

        bool returnValue = false;

        switch (msg->message) {
        case WM_NCCALCSIZE:
            returnValue = this->handleNCCALCSIZE(msg, result);
            break;

        case WM_NCHITTEST:
            returnValue = this->handleNCHITTEST(msg, result);
            break;

        default:
            return QWidget::nativeEvent(eventType, message, result);
        }

        QWidget::nativeEvent(eventType, message, result);

        return returnValue;
    }

private:
    bool handleNCHITTEST(MSG *msg, qintptr *result) {
        const LONG border_width = 8;// in pixels
        RECT winrect;
        GetWindowRect(HWND(winId()), &winrect);

        long x = GET_X_LPARAM(msg->lParam);
        long y = GET_Y_LPARAM(msg->lParam);

        QPoint point(int((qreal) (x - winrect.left) / this->devicePixelRatio()),
                     int((qreal) (y - winrect.top) / this->devicePixelRatio()));

        *result = 0;

        bool resizeWidth = minimumWidth() != maximumWidth();
        bool resizeHeight = minimumHeight() != maximumHeight();

        if (resizeWidth) {
            // left border
            if (x < winrect.left + border_width) {
                *result = HTLEFT;
            }
            // right border
            if (x >= winrect.right - border_width) {
                *result = HTRIGHT;
            }
        }
        if (resizeHeight) {
            // bottom border
            if (y >= winrect.bottom - border_width) {
                *result = HTBOTTOM;
            }
            // top border
            if (y < winrect.top + border_width) {
                *result = HTTOP;
            }
        }
        if (resizeWidth && resizeHeight) {
            // bottom left corner
            if (x >= winrect.left && x < winrect.left + border_width && y < winrect.bottom && y >= winrect.bottom - border_width) {
                *result = HTBOTTOMLEFT;
            }
            // bottom right corner
            if (x < winrect.right && x >= winrect.right - border_width && y < winrect.bottom && y >= winrect.bottom - border_width) {
                *result = HTBOTTOMRIGHT;
            }
            // top left corner
            if (x >= winrect.left && x < winrect.left + border_width && y >= winrect.top && y < winrect.top + border_width) {
                *result = HTTOPLEFT;
            }
            // top right corner
            if (x < winrect.right && x >= winrect.right - border_width && y >= winrect.top && y < winrect.top + border_width) {
                *result = HTTOPRIGHT;
            }
        }

        if (*result == 0) {
            bool client = false;

            if (client) {
                *result = HTCLIENT;
            } else {
                *result = HTCAPTION;
            }
        }

        return true;
    }

    bool handleNCCALCSIZE(MSG *msg, qintptr *result) {
        if (msg->wParam == TRUE) {
            auto *ncp = reinterpret_cast<NCCALCSIZE_PARAMS *>(msg->lParam);

            // ╭─────────────────╮
            // │ Uncomment below │

            // *result = DefWindowProc(msg->hwnd, msg->message, msg->wParam,
            //                         msg->lParam);

            // │ Uncomment above │
            // ╰─────────────────╯

            // remove 1 extra pixel on top of custom frame
            if (ncp) {
                ncp->lppos->flags |= SWP_NOREDRAW;
                ncp->lppos->flags &= ~SWP_DRAWFRAME;
                ncp->rgrc[0].top -= 1;
            }
        }

        *result = 0;
        return true;
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RootWidget root;
    QLabel lbl("Hello world!", &root);
    lbl.resize(200, 100);

    root.show();
    return QApplication::exec();
}

#include "main.moc"
