use super::math2d::{ Vec2, Mat3 };
use crate::glium::Surface;

use std::io::Cursor;

pub struct Transform {
    pub pos: Vec2,
    pub scale: Vec2,
    pub rot: f32,
}

#[derive(Debug, Copy, Clone)]
struct Vertex {
    aPos: [f32; 2],
}

pub struct Rectangle {
    verts: glium::VertexBuffer<Vertex>,
    inds: glium::IndexBuffer<u16>,
    shader: glium::Program,
    transform: Transform,
}


pub fn load_and_compile_shaders(display: &glium::Display, vert_path: &str, frag_path: &str) -> glium::Program {

    let vert_shader = std::fs::read_to_string(vert_path)
        .expect("unable to load vertex shader: {vertPath}");
    let frag_shader = std::fs::read_to_string(frag_path)
        .expect("unable to load fragment shader: {fragPath}");

    return glium::Program::from_source(display, &vert_shader, &frag_shader, None).unwrap();
}

impl Rectangle {

    pub fn new(display: &glium::Display) -> Rectangle {
        let indices = [
            0, 1, 3,
            1, 2, 3u16
        ];

        implement_vertex!(Vertex, aPos);

        let vertex1 = Vertex { aPos: [ 0.5,  0.5] };
        let vertex2 = Vertex { aPos: [ 0.5, -0.5] };
        let vertex3 = Vertex { aPos: [-0.5, -0.5] };
        let vertex4 = Vertex { aPos: [-0.5,  0.5] };
        let shape = vec![vertex1, vertex2, vertex3, vertex4];

        let program = load_and_compile_shaders(&display, "assets/shader.vert", "assets/shader.frag");

        Rectangle {

            verts: glium::VertexBuffer::new(display, &shape).unwrap(),
            inds: glium::IndexBuffer::new(display,
                  glium::index::PrimitiveType::TrianglesList, &indices).unwrap(),
            shader: program,
            transform: Transform {pos: Vec2::newZero(), scale: Vec2::new(1.0, 1.0), rot: 0.0 }
        }
    }

    pub fn draw(&self, target: &mut glium::Frame, view_mat: Mat3) {
        let mut transform = Mat3::scaling(self.transform.scale);
        transform = transform.rotate(self.transform.rot);
        transform = transform.translate(self.transform.pos);

        let uniforms = uniform! {
            transform: transform.data(),
            view: view_mat.data(),
            col: [1.0, 0.0, 0.0f32] 
        };


        target.draw(&self.verts, &self.inds, &self.shader, &uniforms,
                    &Default::default()).unwrap();
    }
}

fn load_texture(display: &glium::Display, path: String) -> glium::texture::SrgbTexture2d {
    let image = image::open(path).unwrap().into_rgba8();
    let image_dimensions = image.dimensions();
    let image = glium::texture::RawImage2d::from_raw_rgba_reversed(&image.into_raw(), image_dimensions);
    let texture = glium::texture::SrgbTexture2d::new(display, image).unwrap();
    texture

}

pub struct Image {
    rect: Rectangle,
    texture: glium::texture::SrgbTexture2d,
}

impl Image {
    pub fn new(display: &glium::Display, path: String) -> Image {
        let texture = load_texture(display, path);
        let (x, y) = texture.dimensions();

        let mut rect = Rectangle::new(display);

        if x > y {
            rect.transform.scale.y = (y / x) as f32;
        }
        else {
            rect.transform.scale.x = (x / y) as f32;
        }

        Image {
            rect: rect,
            texture: texture
        }
    }

    pub fn draw(&self, target: &mut glium::Frame, view_mat: Mat3) {

    }
}
