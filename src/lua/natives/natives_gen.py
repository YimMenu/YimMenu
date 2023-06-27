import os

natives_hpp = open("../../natives.hpp", "r")

cpp_print_buf = ""
hpp_print_buf = ""


def print_cpp(text):
    global cpp_print_buf
    cpp_print_buf += text + "\n"


def print_hpp(text):
    global hpp_print_buf
    hpp_print_buf += text + "\n"


class Arg:
    def __init__(self, name, type_):
        self.name = name
        self.type_ = type_

    def __str__(self) -> str:
        return str(self.type_) + " " + str(self.name)


class NativeFunc:
    def __init__(self, name, args, return_type):
        self.name = name
        self.args = args
        self.return_type = return_type

    def __str__(self) -> str:
        if len(self.args) > 0:
            return (
                str(self.return_type)
                + " "
                + str(self.name)
                + "( "
                + str(self.args[0])
                + " )"
            )
        else:
            return str(self.return_type) + " " + str(self.name) + "( )"


def get_natives_func_from_natives_hpp_file(natives_hpp):
    functions_per_namespaces = {}
    current_namespace = ""
    func_name = ""
    start_parsing = False
    for line in natives_hpp.readlines():
        if "namespace SYSTEM" not in line and not start_parsing:
            continue
        else:
            start_parsing = True

        if not start_parsing:
            continue

        if "namespace " in line:
            current_namespace = line.replace("namespace ", "").strip()
            functions_per_namespaces[current_namespace] = []
        elif "NATIVE_DECL" in line:
            words = line.split()

            # remove NATIVE_DECL from the words array
            words.pop(0)

            func_name = ""
            return_type = [x for x in words if "(" not in x][0]

            for word in words:
                # function name + args
                if "(" in word:
                    if func_name == "":
                        func_name_and_args = word.split("(")
                        func_name = func_name_and_args[0]
                    continue

            functions_per_namespaces[current_namespace].append(
                NativeFunc(func_name, [], return_type)
            )

    return functions_per_namespaces


functions_per_namespaces = get_natives_func_from_natives_hpp_file(natives_hpp)


def generate_native_binding_cpp_and_hpp_file(functions_per_namespaces):
    generated_function_name = "void init_native_binding(sol::state& L)"

    print_hpp("#pragma once")
    print_hpp('#include "lua/sol.hpp"')
    print_hpp("")
    print_hpp("namespace lua::native")
    print_hpp("{")
    print_hpp("\t" + generated_function_name + ";")
    print_hpp("}")

    print_cpp('#include "lua_native_binding.hpp"')
    print_cpp('#include "natives.hpp"')
    print_cpp("")
    print_cpp("namespace lua::native")
    print_cpp("{")
    print_cpp("\t" + generated_function_name)
    print_cpp("\t{")

    i = 0
    for namespace_name, native_funcs in functions_per_namespaces.items():
        print_cpp(
            "\t\tauto "
            + namespace_name
            + ' = L["'
            + namespace_name
            + '"].get_or_create<sol::table>();'
        )

        for native_func in native_funcs:
            i += 1
            print_cpp(
                "\t\t"
                + namespace_name
                + '.set_function("'
                + native_func.name
                + '", '
                + namespace_name
                + "::"
                + native_func.name
                + ");"
            )

        print_cpp("")

    print(f"Wrote binding for {i} native functions")
    print_cpp("\t}")
    print_cpp("}")


generate_native_binding_cpp_and_hpp_file(functions_per_namespaces)


def write_cpp_code(cpp_print_buf):
    file_name = "lua_native_binding.cpp"
    if os.path.exists(file_name):
        os.remove(file_name)
    f = open(file_name, "a")
    f.write(cpp_print_buf)
    f.close()


def write_hpp_code(hpp_print_buf):
    file_name = "lua_native_binding.hpp"
    if os.path.exists(file_name):
        os.remove(file_name)
    f = open(file_name, "a")
    f.write(hpp_print_buf)
    f.close()


write_cpp_code(cpp_print_buf)
write_hpp_code(hpp_print_buf)
