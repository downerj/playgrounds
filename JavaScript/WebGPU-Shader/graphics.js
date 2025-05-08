export class Graphics3D {
  #gpu;
  #adapter;
  #device;
  /**
   * @type {HTMLCanvasElement}
   */
  #canvas;
  #context;
  #renderPipeline;
  #vertices;
  #vertexBuffer;

  /**
   * 
   * @param {HTMLCanvasElement} canvas
   */
  constructor(canvas) {
    this.#canvas = canvas;
  }

  /**
   * 
   * @param {HTMLCanvasElement} canvas
   * @returns {Promise<void>}
   */
  async init() {
    this.#gpu = navigator.gpu;
    if (!this.#gpu) {
      throw Error("WebGPU not supported");
    }
    this.#adapter = await this.#gpu.requestAdapter();
    if (!this.#adapter) {
      throw Error("Couldn't request WebGPU adapter.");
    }
    this.#device = await this.#adapter.requestDevice();
    /**
     * @type {HTMLScriptElement}
     */
    const shadersElement = document.getElementById('wgsl-shaders');
    const shaderModule = this.#device.createShaderModule({
      code: shadersElement.textContent,
    });
    this.#context = this.#canvas.getContext("webgpu");
    this.#context.configure({
      device: this.#device,
      format: this.#gpu.getPreferredCanvasFormat(),
      alphaMode: "premultiplied",
    });
    this.#vertices = new Float32Array([
      // Vertex 1
      -1, -1, 0, 1, // XYZW
      1, 0, 0, 1, // RGBA
      // Vertex 2
      1, -1, 0, 1, // XYZW
      0, 1, 0, 1, // RGBA
      // Vertex 3
      0, 1, 0, 1, // XYZW
      0, 0, 1, 1, // RGBA
    ]);
    this.#vertexBuffer = this.#device.createBuffer({
      size: this.#vertices.byteLength,
      usage: GPUBufferUsage.VERTEX | GPUBufferUsage.COPY_DST,
    });
    this.#device.queue.writeBuffer(this.#vertexBuffer, 0, this.#vertices, 0, this.#vertices.length);
    this.#renderPipeline = this.#device.createRenderPipeline({
      vertex: {
        module: shaderModule,
        entryPoint: "vertex_main",
        buffers: [{
          attributes: [{
            shaderLocation: 0, // position
            offset: 0,
            format: "float32x4",
          }, {
            shaderLocation: 1, // color
            offset: 16,
            format: "float32x4",
          }],
          arrayStride: 32,
          stepMode: "vertex",
        }],
      },
      fragment: {
        module: shaderModule,
        entryPoint: "fragment_main",
        targets: [{
          format: this.#gpu.getPreferredCanvasFormat(),
        }],
      },
      primitive: {
        topology: "triangle-list",
        frontFace: "ccw",
      },
      layout: "auto",
    });
  }

  /**
   * 
   * @param {DOMHighResTimeStamp} _timestamp
   */
  render(_timestamp) {
    const commandEncoder = this.#device.createCommandEncoder();
    const passEncoder = commandEncoder.beginRenderPass({
      colorAttachments: [{
        clearValue: { r: 0.0, g: 0.5, b: 1.0, a: 1.0 },
        loadOp: "clear",
        storeOp: "store",
        view: this.#context.getCurrentTexture().createView(),
      }],
    });
    passEncoder.setPipeline(this.#renderPipeline);
    passEncoder.setVertexBuffer(0, this.#vertexBuffer);
    passEncoder.draw(3);
    passEncoder.end();
    this.#device.queue.submit([commandEncoder.finish()]);
  }
}
