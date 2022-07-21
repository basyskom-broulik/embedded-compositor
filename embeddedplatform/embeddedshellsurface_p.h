#ifndef EMBEDDEDSHELLSURFACE_P_H
#define EMBEDDEDSHELLSURFACE_P_H
#include "embeddedshellsurface.h"
#include "qwayland-embedded-shell.h"
#include <QDebug>
#include <QtWaylandClient/private/qwaylandshellsurface_p.h>

class EmbeddedShellSurfacePrivate
    : public QtWaylandClient::QWaylandShellSurface,
      public QtWayland::embedded_shell_surface {
  Q_DECLARE_PUBLIC(EmbeddedShellSurface)
  Q_OBJECT
public:
  using Anchor = EmbeddedShellSurface::Anchor;
  EmbeddedShellSurfacePrivate(struct ::embedded_shell_surface *shell_surface,
                              QtWaylandClient::QWaylandWindow *window,
                              Anchor anchor);
  ~EmbeddedShellSurfacePrivate() override;
  Anchor getAnchor() const { return m_anchor; }

  void applyConfigure() override;

private:
  EmbeddedShellSurface::Anchor m_anchor;
  QSize m_pendingSize = {0, 0};
  EmbeddedShellSurface *q_ptr = nullptr;

protected:
  void embedded_shell_surface_configure(int32_t width, int32_t height) override;
};

class EmbeddedShellSurfaceViewPrivate : public QObject,
                                        public QtWayland::surface_view {
  Q_DECLARE_PUBLIC(EmbeddedShellSurfaceView)
  Q_OBJECT
  QString m_label;

public:
  EmbeddedShellSurfaceViewPrivate(EmbeddedShellSurfaceView *q,
                                  ::surface_view *view,
                                  EmbeddedShellSurface *surf,
                                  const QString &label);
  void surface_view_selected() override {
    qDebug() << __PRETTY_FUNCTION__;
    Q_Q(EmbeddedShellSurfaceView);
    emit q->selected();
  }
  EmbeddedShellSurfaceView *q_ptr = nullptr;
};
#endif // EMBEDDEDSHELLSURFACE_P_H
