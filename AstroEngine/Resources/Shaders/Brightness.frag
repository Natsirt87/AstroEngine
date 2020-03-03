uniform sampler2D source;

varying vec2 vTexCoord;

const float Threshold = 0.55;
const float Factor   = 2.5;

void main()

{
	vec4 sourceFragment = texture2D(source, vTexCoord);
	float luminance = sourceFragment.r * 0.2126 + sourceFragment.g * 0.7152 + sourceFragment.b * 0.0722;
	sourceFragment *= clamp(luminance - Threshold, 0.0, 1.0) * Factor;
	gl_FragColor = sourceFragment;
}