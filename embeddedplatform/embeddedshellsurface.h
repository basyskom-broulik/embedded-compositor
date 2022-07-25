#ifndef EMBEDDEDSHELLSURFACE_H
#define EMBEDDEDSHELLSURFACE_H

#include "embeddedplatform.h"
#include <QObject>

class EmbeddedShellSurfaceView;
class EmbeddedShellSurfaceViewPrivate;
class EmbeddedShellSurfacePrivate;

struct embedded_shell_surface;
struct surface_view;
class QWindow;

namespace QtWaylandClient {
class QWaylandWindow;
class QWaylandShellSurface;
} // namespace QtWaylandClient

class Q_DECL_EXPORT EmbeddedShellSurface : public QObject {
  Q_OBJECT
  Q_DECLARE_PRIVATE(EmbeddedShellSurface)
  QScopedPointer<EmbeddedShellSurfacePrivate> d_ptr;

public:
  using Anchor = EmbeddedPlatform::Anchor;

  EmbeddedShellSurface(struct ::embedded_shell_surface *shell_surface,
                       QtWaylandClient::QWaylandWindow *window, Anchor anchor);
  ~EmbeddedShellSurface() override;

  Anchor getAnchor() const;
  EmbeddedShellSurfaceView *createView(const QString &label);

  QtWaylandClient::QWaylandShellSurface *shellSurface();
signals:

public slots:
  void sendAnchor(Anchor anchor);
};

class EmbeddedShellSurfaceView : public QObject {
  Q_OBJECT
  Q_DECLARE_PRIVATE(EmbeddedShellSurfaceView)
  QScopedPointer<EmbeddedShellSurfaceViewPrivate> d_ptr;
  Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)

public:
  EmbeddedShellSurfaceView(struct ::surface_view *view,
                           EmbeddedShellSurface *surf, const QString &label);
  ~EmbeddedShellSurfaceView() override;

  const QString &label() const;
  void setLabel(const QString &newLabel);

signals:
  void selected();
  void labelChanged();
};

#endif // EMBEDDEDSHELLSURFACE_H