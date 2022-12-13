use std::ops;


#[derive(Debug, Copy, Clone)]
pub struct Vec2 {
    pub x: f32,
    pub y: f32,
}

impl Vec2 {
    pub fn to_array(&self) -> [f32; 2] {
        [self.x, self.y]
    }

    pub fn magnitude(&self) -> f32 {
        f32::sqrt(self.x*self.x + self.y*self.y)
    }

    pub fn normalize(&self) -> Vec2 {
        let mag = self.magnitude();
        Vec2 {x: self.x / mag, y:self.y / mag }
    }

    pub fn scale(&self, scalar: f32) -> Vec2 {
        Vec2 {x: self.x * scalar, y: self.y * scalar}
    }

    pub fn dot(&self, other: &Vec2) -> f32 {
        self.x * other.x + self.y * other.y
    }

    pub fn angle_to(&self, other: &Vec2) -> f32 {
        f32::atan2(self.x * other.y - self.y * other.x, self.x * other.x + self.y * other.y)
    }

    pub fn rotate(&self, angle: f32) -> Vec2 {
        Vec2 {x: self.x * f32::cos(angle) - self.y * f32::sin(angle), y: self.x * f32::sin(angle) + self.y * f32::cos(angle)}
    }

    pub fn lerp_to(&self, other: &Vec2, t: f32) -> Vec2 {
        //self + (other - self) * t
        Vec2 {x: 0.0, y: 0.0}
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
