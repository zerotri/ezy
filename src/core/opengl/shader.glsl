//------------------------------------------------------------------------------
//  shader for sprite renderer
//------------------------------------------------------------------------------
@ctype mat4 hmm_mat4

@vs vs
uniform vs_params {
  mat4 proj;
};

in vec2 position;
in vec4 color0;
in vec2 texcoord0;

out vec2 uv;
out vec4 color;

void main() {
  gl_Position = proj * vec4(position, 0.0, 1.0);
  color = color0;
  uv = texcoord0;
}
@end

@fs fs
uniform sampler2D tex;

in vec2 uv;
in vec4 color;

out vec4 frag_color;

void main() {
  frag_color = texture(tex, uv) * color;
}
@end

@program sprite vs fs

