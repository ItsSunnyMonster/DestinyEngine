//@begin_vert
    #version 450

    layout (location = POSITION)  in  vec2 a_Pos;
        
    void main() {
        gl_Position = vec4(a_Pos, 1.0, 1.0);
    }
//@end

//@begin_frag
    #version 450
    layout (location = SV_Target0) out vec4 o_FragColour;

    void main() {
        o_FragColour = vec4(119.0 / 256.0, 221.0 / 256.0, 119.0 / 256.0, 1.0);
    }
//@end