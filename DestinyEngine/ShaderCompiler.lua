rule "ShaderCompiler"
    display "Shader Compiler"
    fileextension ".glsl"

    buildmessage "Compiling shader %(Filename)%(Extension)"
    buildcommands "vendor\\shader-compiling\\glslcc.exe %(FullPath) --output=assets/shaders/hlsl/%(Filename).cso --lang=hlsl --reflect --bin"
    buildoutputs {"assets/shaders/hlsl/%(Filename).cso", "assets/shaders/hlsl/%(Filename).cso.json"}