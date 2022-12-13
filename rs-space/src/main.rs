#[macro_use]
extern crate glium;

pub mod rfg;

use rfg::graphics2d::*;
use rfg::math2d::Vec2;

fn main() {
    #[allow(unused_imports)]
    use glium::{glutin, Surface};

    let event_loop = glutin::event_loop::EventLoop::new();
    let wb = glutin::window::WindowBuilder::new();
    let cb = glutin::ContextBuilder::new();
    let display = glium::Display::new(wb, cb, &event_loop).unwrap();

    #[derive(Copy, Clone)]
    struct Vertex {
        aPos: [f32; 2],
    }

    implement_vertex!(Vertex, aPos);

    let vertex1 = Vertex { aPos: [-0.5, -0.5] };
    let vertex2 = Vertex { aPos: [ 0.0,  0.5] };
    let vertex3 = Vertex { aPos: [ 0.5, -0.25] };
    let shape = vec![vertex1, vertex2, vertex3];

    let vertex_buffer = glium::VertexBuffer::new(&display, &shape).unwrap();
    let indices = glium::index::NoIndices(glium::index::PrimitiveType::TrianglesList);

    let program = load_and_compile_shaders(&display, "assets/shader.vert", "assets/shader.frag");

    //let program = glium::Program::from_source(&display, vertex_shader_src, fragment_shader_src, None).unwrap();
    
    let uniforms = uniform! {
        transform: [
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0],
            [0.0, 0.0, 1.0f32],
        ],
        view: [
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0],
            [0.0, 0.0, 1.0f32],
        ],
        col: [1.0, 0.0, 0.0f32] 
    };

    let a = Vec2 {x: 2.0, y: 1.0};
    let b = Vec2 {x: 1.0, y: 1.0};


    let mut c = a * 0.1;
    let d = a * b;
    c = a - b;


    println!("a - b: {:?}", a - b);

    event_loop.run(move |event, _, control_flow| {
        let next_frame_time = std::time::Instant::now() +
            std::time::Duration::from_nanos(16_666_667);
        *control_flow = glutin::event_loop::ControlFlow::WaitUntil(next_frame_time);

        match event {
            glutin::event::Event::WindowEvent { event, .. } => match event {
                glutin::event::WindowEvent::CloseRequested => {
                    *control_flow = glutin::event_loop::ControlFlow::Exit;
                    return;
                },
                _ => return,
            },
            glutin::event::Event::NewEvents(cause) => match cause {
                glutin::event::StartCause::ResumeTimeReached { .. } => (),
                glutin::event::StartCause::Init => (),
                _ => return,
            },
            _ => return,
        }

        let mut target = display.draw();
        target.clear_color(0.1, 0.1, 0.1, 1.0);
        target.draw(&vertex_buffer, &indices, &program, &uniforms,
                    &Default::default()).unwrap();
        target.finish().unwrap();
    });
}
