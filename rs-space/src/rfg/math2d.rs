use std::ops;


#[derive(Debug, Copy, Clone)]
pub struct Vec2 {
    pub x: f32,
    pub y: f32,
}


impl Vec2 {
    pub fn newZero() -> Vec2{
        Vec2 { x: 0.0, y: 0.0 }
    }

    pub fn new(x: f32, y: f32) -> Vec2{
        Vec2 { x: x, y: y }
    }

    pub fn to_array(&self) -> [f32; 2] {
        [self.x, self.y]
    }

    pub fn magnitude(self) -> f32 {
        f32::sqrt(self.x*self.x + self.y*self.y)
    }

    pub fn normalize(self) -> Vec2 {
        let mag = self.magnitude();
        Vec2 {x: self.x / mag, y:self.y / mag }
    }

    pub fn scale(self, scalar: f32) -> Vec2 {
        Vec2 {x: self.x * scalar, y: self.y * scalar}
    }

    pub fn dot(self, other: &Vec2) -> f32 {
        self.x * other.x + self.y * other.y
    }

    pub fn angle_to(self, other: &Vec2) -> f32 {
        f32::atan2(self.x * other.y - self.y * other.x, self.x * other.x + self.y * other.y)
    }

    pub fn rotate(self, angle: f32) -> Vec2 {
        Vec2 {x: self.x * f32::cos(angle) - self.y * f32::sin(angle), y: self.x * f32::sin(angle) + self.y * f32::cos(angle)}
    }

    pub fn lerp_to(self, other: Vec2, t: f32) -> Vec2 {
        self + (other - self) * t
    }
}

impl ops::Add<Vec2> for Vec2 {
    type Output = Vec2;

    fn add(self, _rhs: Vec2) -> Vec2 {
        Vec2 { x: self.x + _rhs.x, y: self.y + _rhs.y }
    }
}

impl ops::Sub<Vec2> for Vec2 {
    type Output = Vec2;

    fn sub(self, _rhs: Vec2) -> Vec2 {
        Vec2 { x: self.x - _rhs.x, y: self.y - _rhs.y }
    }
}

impl ops::Mul<Vec2> for Vec2 {
    type Output = f32;

    fn mul(self, _rhs: Vec2) -> f32 {
        self.dot(&_rhs)
    }
}

impl ops::Mul<f32> for Vec2 {
    type Output = Vec2;

    fn mul(self, _rhs: f32) -> Vec2 {
        self.scale(_rhs)
    }
}


#[derive(Debug, Copy, Clone)]
pub struct Mat3 {
    data: [[f32; 3]; 3],
}

impl Mat3 {
    pub fn index() -> Mat3 {
        Mat3 { data: [[1.0, 0.0, 0.0],
                      [0.0, 1.0, 0.0],
                      [0.0, 0.0, 1.0f32]] }
    }

    pub fn data(&self) -> [[f32; 3]; 3] {
        self.data
    }

    pub fn rotation(angle: f32) -> Mat3 {
        Mat3 {data: [
            [f32::cos(angle), -f32::sin(angle), 0.0],
            [f32::sin(angle), f32::cos(angle),  0.0],
            [0.0,             0.0,              1.0f32],
        ]}
    }

    pub fn scaling(scale: Vec2) -> Mat3 {
        Mat3 {data: [
            [scale.x, 0.0,      0.0],
            [0.0,     scale.y,  0.0],
            [0.0,     0.0,      1.0f32],
        ]}
    }

    pub fn translateion(translate: Vec2) -> Mat3 {
        Mat3 {data: [
            [1.0, 0.0, translate.x],
            [0.0, 1.0, translate.y],
            [0.0, 0.0, 1.0f32],
        ]}
    }

    pub fn rotate(&self, angle: f32) -> Mat3 {
        Mat3::rotation(angle) * *self
    }

    pub fn scale(&self, scale: Vec2) -> Mat3 {
        Mat3::scaling(scale) * *self
    }

    pub fn translate(&self, translate: Vec2) -> Mat3 {
        Mat3::translateion(translate) * *self
    }

    pub fn multiply(self, other: Mat3) -> Mat3 {
        Mat3 {data: [[
            self.data[0][0] * other.data[0][0] + self.data[0][1] * other.data[1][0] + self.data[0][2] * other.data[2][0],
            self.data[0][0] * other.data[0][1] + self.data[0][1] * other.data[1][1] + self.data[0][2] * other.data[2][1],
            self.data[0][0] * other.data[0][2] + self.data[0][1] * other.data[1][2] + self.data[0][2] * other.data[2][2],
        ], [
            self.data[1][0] * other.data[0][0] + self.data[1][1] * other.data[1][0] + self.data[1][2] * other.data[2][0],
            self.data[1][0] * other.data[0][1] + self.data[1][1] * other.data[1][1] + self.data[1][2] * other.data[2][1],
            self.data[1][0] * other.data[0][2] + self.data[1][1] * other.data[1][2] + self.data[1][2] * other.data[2][2],
        ], [
            self.data[2][0] * other.data[0][0] + self.data[2][1] * other.data[1][0] + self.data[2][2] * other.data[2][0],
            self.data[2][0] * other.data[0][1] + self.data[2][1] * other.data[1][1] + self.data[2][2] * other.data[2][1],
            self.data[2][0] * other.data[0][2] + self.data[2][1] * other.data[1][2] + self.data[2][2] * other.data[2][2],
        ]]}
    }

    pub fn point_in_path(point: Vec2 , poly: &[Vec2], poly_length: usize) -> bool {
        let mut j = poly_length - 1;
        let mut c = false;

        for i in 0..poly_length {
            if (point.x == poly[i].x) && (point.y == poly[i].y) {
                // point is a corner
                return true;
            }
            if (poly[i].y > point.y) != (poly[j].y > point.y) {
                let slope = (point.x - poly[i].x) * (poly[j].y - poly[i].y) - (poly[j].x-poly[i].x) * (point.y-poly[i].y);

                if slope == 0.0 {
                    // point is on boundary
                    return true;
                }
                if (slope < 0.0) != (poly[j].y < poly[i].y) {
                    c = !c;
                }
            }
            j = i;
        }
        c
    }
}

impl ops::Mul<Mat3> for Mat3 {
    type Output = Mat3;

    fn mul(self, other: Mat3) -> Mat3 {
        self.multiply(other)
    }
}

impl ops::Index<usize> for Mat3 {
    type Output = [f32];

    fn index(&self, i: usize) -> &[f32]{
        &self.data[i]
    }
}
