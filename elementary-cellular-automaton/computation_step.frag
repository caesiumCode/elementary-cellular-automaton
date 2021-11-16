#version 120

uniform float width;
uniform sampler2D previous;

uniform bool rule000;
uniform bool rule001;
uniform bool rule010;
uniform bool rule011;
uniform bool rule100;
uniform bool rule101;
uniform bool rule110;
uniform bool rule111;

void main() {
    const float ON = 0.0;
    const float OFF = 1.0;
    const vec4 ON_COLOR = vec4(ON, ON, ON, 1.0);
    const vec4 OFF_COLOR = vec4(OFF, OFF, OFF, 1.0);
    
    vec2 RESOLUTION = vec2(width, 1.0);
    
    vec2 middle = gl_FragCoord.xy;
    vec2 left = middle + vec2(-1.0, 0.0);
    vec2 right = middle + vec2(1.0, 0.0);
    
    float middle_col = texture2D(previous, middle / RESOLUTION).x;
    float left_col = texture2D(previous, left / RESOLUTION).x;
    float right_col = texture2D(previous, right / RESOLUTION).x;
    
    if (left_col == OFF && middle_col == OFF && right_col == OFF) {
        if (rule000)
            gl_FragColor = ON_COLOR;
        else
            gl_FragColor = OFF_COLOR;
    } else if (left_col == OFF && middle_col == OFF && right_col == ON) {
        if (rule001)
            gl_FragColor = ON_COLOR;
        else
            gl_FragColor = OFF_COLOR;
    } else if (left_col == OFF && middle_col == ON && right_col == OFF) {
        if (rule010)
            gl_FragColor = ON_COLOR;
        else
            gl_FragColor = OFF_COLOR;
    } else if (left_col == OFF && middle_col == ON && right_col == ON) {
        if (rule011)
            gl_FragColor = ON_COLOR;
        else
            gl_FragColor = OFF_COLOR;
    } else if (left_col == ON && middle_col == OFF && right_col == OFF) {
        if (rule100)
            gl_FragColor = ON_COLOR;
        else
            gl_FragColor = OFF_COLOR;
    } else if (left_col == ON && middle_col == OFF && right_col == ON) {
        if (rule101)
            gl_FragColor = ON_COLOR;
        else
            gl_FragColor = OFF_COLOR;
    } else if (left_col == ON && middle_col == ON && right_col == OFF) {
        if (rule110)
            gl_FragColor = ON_COLOR;
        else
            gl_FragColor = OFF_COLOR;
    } else if (left_col == ON && middle_col == ON && right_col == ON) {
        if (rule111)
            gl_FragColor = ON_COLOR;
        else
            gl_FragColor = OFF_COLOR;
    }
}
