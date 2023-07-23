import os

def split_natives_hpp_into_hpp_and_cpp(natives_hpp, output_hpp, output_cpp):
    hpp_buf = ""
    cpp_buf = '#include "natives.hpp"\n\n'

    with open(natives_hpp, 'r') as natives_hpp_content:
        cpp_start_parsing = False
        for line in natives_hpp_content:
            if line.startswith("namespace "):
                hpp_buf += line
                cpp_buf += line
                cpp_start_parsing = True
                continue
            if "static" not in line:
                hpp_buf += line
                if cpp_start_parsing:
                    cpp_buf += line
                continue
            #if "(" not in line:
                #hpp_buf += line
                #if cpp_start_parsing:
                #    cpp_buf += line
                #continue


            line = line.replace("static ", "")

            index_of_body_start = line.find("{")
            if index_of_body_start != 1:
                hpp_buf += line[:index_of_body_start].rstrip() + ";\n"

            cpp_buf += line


    if os.path.exists(output_hpp):
        os.remove(output_hpp)
    f = open(output_hpp, "a")
    f.write(hpp_buf)
    f.close()
    
    if os.path.exists(output_cpp):
        os.remove(output_cpp)
    f = open(output_cpp, "a")
    f.write(cpp_buf)
    f.close()

split_natives_hpp_into_hpp_and_cpp("natives.hpp", "natives.hpp", "natives.cpp")
