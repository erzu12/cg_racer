
pub fn load_and_compile_shaders(display: &glium::Display, vert_path: &str, frag_path: &str) -> glium::Program {

    let vert_shader = std::fs::read_to_string(vert_path)
        .expect("unable to load vertex shader: {vertPath}");
    let frag_shader = std::fs::read_to_string(frag_path)
        .expect("unable to load fragment shader: {fragPath}");

    return glium::Program::from_source(display, &vert_shader, &frag_shader, None).unwrap();
}
