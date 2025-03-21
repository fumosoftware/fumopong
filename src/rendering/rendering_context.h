//
// Created by fumosoftware on 3/20/2025.
//

#ifndef RENDERING_CONTEXT_H
#define RENDERING_CONTEXT_H
#include <memory>
#include <expected>


class IRenderingContextDevice;
class IWindow;
class RenderingContext {
public:
  explicit RenderingContext(std::unique_ptr<IRenderingContextDevice>&& context_device);
  ~RenderingContext();
  RenderingContext(RenderingContext&&) noexcept;
  RenderingContext& operator=(RenderingContext&&) noexcept;

  [[nodiscard]] IWindow* get_main_window() const noexcept;
private:
  std::unique_ptr<IRenderingContextDevice> m_context_device{nullptr};
};

std::expected<RenderingContext, std::string> create_rendering_context();

#endif //RENDERING_CONTEXT_H
