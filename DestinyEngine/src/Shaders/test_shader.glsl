//@begin_vert
    #version 450

    layout (location = POSITION)  in  vec2 a_Pos;
    layout (location = COLOR0)    in  vec3 a_Colour;

    layout (location = COLOR0)    out vec3 f_Colour;
        
    void main() {
        f_Colour = a_Colour;
        gl_Position = vec4(a_Pos, 1.0, 1.0);
    }
//@end

//@begin_frag
    #version 450
    layout (location = COLOR0)    in vec3 f_Colour;

    layout (location = SV_Target0) out vec4 o_FragColour;

    void main() {
        o_FragColour = vec4(f_Colour, 1.0);
    }
//@end