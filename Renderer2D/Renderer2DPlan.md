# Renderer2D Overview

> This will just go over the plan, for how i want the Renderer2D to work.

## Renderer2D
  > The top down API to be used by the programmer

It should be simple to use it, and not require any setup, or interaction with the actual RenderAPI.
We should be able to draw our sprite to the screen, using a simple method like Renderer2D::Draw(...).

The Renderer2D::Draw(...) should only care about 2 things.
  [1] Where? - For this we will provide a Transform2D component or something similar.
  [2] How? - To determine how it should look, we use a Texture, and possibly a tint.

The final Draw API will then be Renderer2D::Draw(Transform2D transform, Texture texture, Color tint)
The question in now; What if we want to draw a solid color, and what if i don't want a tint?

Answer:
To deal with the solid color, we will just have a purely white texture, we apply by default. i.e. (.., Texture texture = s_WhiteTexture, ..).
To deal with the tint, we do something similar. We apply a default purely white tint, i.e. (..., Color tint = White).

The final Draw() is then Renderer2D::Draw(Transform2D transform, Texture texture = s_WhiteTexture, Color tint = White).

Now we have 2 additional concerns.
  [1] We don't want the programmer to transform the global coordinates into screenspace.
  [2] We don't want to issue 1000+ drawcalls every frame. This would cause massive overhead.

To get around this, we create the idea of a scene. The scene will hold the transform from global to screenspace.
It will also track all the things we want to draw, and dispatch the in a batch to the renderer. So in addition to the drawing,
we will also need methods to set up a scene, and to end the scene (Issue the draw calls).

BeginScene(const Camera& camera)
EndScene()

The final interface would then be something similar to:
BeginScene(camera)
{
  DrawQuad(...);
  DrawQuad(...);
  Draw...
}
EndScene();

## RendererManager
  > The coordinator and global state manager.

It should sit below the Renderer2D, and orchestrate the rendering cycle.
It should shield the Renderer2D, from the active RendererAPI.

The RendererManager should only care about 2 things:
  [1] Who is doing the work? It will need to hold a reference to the active graphics backend (e.g. OpenGL or Vulcan).
  [2] What is the global environment? It dictates the config for the whole screen (e.g. ScreenSize or ClearColor).

The API will then be something like: RendererManager::Init(GraphicsAPI API), to initialize the renderer,
and RendererManager::SetViewport(uint32_t newWidth, uint32_t newHeight).

We then have one additional concern.
  [1] We don't want the Renderer2D calling OpenGL/Vulkan methods directly, to call its batches.

To deal with this, the RendererManager will act as a generic forwarder, passing the commands along to the appropriate backend.

## RendererAPI
 > The hardware abstraction interface.

It should be a pure virtual interface, that dictates the capabilities of what the backend can do.
It should know nothing of the higher level abstraction, and should only care about raw GPU data.

The RendererAPI should only care about 1 thing.
  [1] Executing commands, like clearing the screen, or drawing the list of triangles or changing state dictated by the RenderManager.

