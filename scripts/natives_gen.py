# working dir: scripts
# python ./natives_gen.py

import os

natives_hpp = open("../src/natives.hpp", "r")

cpp_print_buf = ""
hpp_print_buf = ""

hpp_lua_native_wrappers_print_buf = ""


def print_cpp(text):
    global cpp_print_buf
    cpp_print_buf += text + "\n"


def print_hpp(text):
    global hpp_print_buf
    hpp_print_buf += text + "\n"


class Arg:
    def __init__(self, name, type_):
        self.name = name
        self.type_ = type_.replace("BOOL", "bool").replace("Any*", "uintptr_t")
        if self.type_ == "uintptr_t":
            self.is_any_ptr = True
        else:
            self.is_any_ptr = False
        if self.type_ == "const char*":
            self.type_ = self.type_.replace("const char*", "sol::stack_object")
            self.is_string = True
        else:
            self.is_string = False
        self.is_pointer_arg = "*" in self.type_ and "const char" not in self.type_
        self.type_no_star = self.type_.replace("*", "")

    def __str__(self) -> str:
        return str(self.type_) + " " + str(self.name)


class NativeFunc:
    def __init__(self, namespace, lua_name, cpp_name, args, return_type):
        self.namespace = namespace
        self.lua_name = lua_name
        self.cpp_name = cpp_name
        self.args = args
        self.return_type = return_type.replace("BOOL", "bool").replace("Any*", "uintptr_t")

        self.out_params = []
        if self.return_type != "void":
            retvalArg = Arg("retval", self.return_type)
            # Any* case: this is incorrect but
            # we'd need a custom lua usertype and write code for it inside the native function wrappers,
            # it also only affect some of the DATAFILE natives.
            retvalArg.is_pointer_arg = False
            self.out_params.append(retvalArg)
        for arg in self.args:
            if arg.is_pointer_arg:
                self.out_params.append(arg)

    def __str__(self) -> str:
        s = ""

        returning_multiple_values = False
        tuple_type = ""
        fixed_return = self.return_type
        if len(self.out_params) > 1:
            fixed_return = "std::tuple<"
            for out_param in self.out_params:
                if out_param.is_pointer_arg:
                    fixed_return += out_param.type_no_star + ", "
                else:
                    fixed_return += ("const char*" if out_param.is_string else out_param.type_) + ", "
            fixed_return = fixed_return[:-2] + ">"
            returning_multiple_values = True
            tuple_type = fixed_return
        elif len(self.out_params) == 1:
            if self.out_params[0].is_pointer_arg:
                fixed_return = self.out_params[0].type_no_star
            else:
                fixed_return = ("const char*" if self.out_params[0].is_string else self.out_params[0].type_)

        fixed_params = ""
        if len(self.args) > 0:
            for arg in self.args:
                if not arg.is_pointer_arg:
                    fixed_params += arg.type_ + " " + arg.name + ", "
                else:
                    fixed_params += arg.type_no_star + " " + arg.name + ", "
            fixed_params = fixed_params[:-2]

        s += (
            fixed_return
            + " "
            + "LUA_NATIVE_"
            + self.namespace
            + "_"
            + self.lua_name
            + "("
            + fixed_params
            + ")"
        )

        s += "\n"
        s += "\t{\n"

        if self.cpp_name == "ADD_OWNED_EXPLOSION":
            s+= "\t\tbig::explosion_anti_cheat_bypass::apply();\n\n"

        call_native = "\t\t"
        if len(self.out_params) > 0:
            if returning_multiple_values:
                tuple_declaration = tuple_type + " return_values;"
                s += "\t\t" + tuple_declaration + "\n"
                if self.return_type != "void":
                    call_native += "std::get<0>(return_values) = "
                    if self.return_type == "bool":
                        call_native += "(bool)"
            elif self.return_type != "void":
                call_native += "auto retval = "
                if self.return_type == "bool":
                    call_native += "(bool)"

            call_native += self.namespace + "::" + self.cpp_name + "("
        else:
            call_native += self.namespace + "::" + self.cpp_name + "("

        if len(self.args) > 0:
            for arg in self.args:
                if arg.is_any_ptr:
                    call_native += "(Any*)"

                if arg.is_pointer_arg:
                    if arg.type_ == "bool*":
                        call_native += "(BOOL*)"
                    call_native += "&"
                    

                if arg.is_string:
                    call_native += f'{arg.name}.is<const char*>() ? {arg.name}.as<const char*>() : nullptr, '
                else:
                    call_native += arg.name + ", "
            call_native = call_native[:-2]

        call_native += ");"

        s += call_native

        if self.cpp_name == "ADD_OWNED_EXPLOSION":
            s+= "\n\n\t\tbig::explosion_anti_cheat_bypass::restore();"

        if returning_multiple_values:
            assign_return_values = "\n"
            if self.return_type != "void":
                i = 1
            else:
                i = 0
            for arg in self.args:
                if arg.is_pointer_arg:
                    assign_return_values += (
                        "\t\tstd::get<"
                        + str(i)
                        + ">(return_values) = "
                        + arg.name
                        + ";\n"
                    )
                    i += 1
            s += assign_return_values

        return_statement = ""
        if len(self.out_params) > 0:
            if returning_multiple_values:
                return_statement = "return return_values;"
            elif self.return_type != "void":
                if self.return_type == "uintptr_t":
                    return_statement = "return (uintptr_t)retval;"
                else:
                    return_statement = "return retval;"
            else:
                for arg in self.args:
                    if arg.is_pointer_arg:
                        return_statement = "return " + arg.name + ";"
            s += "\n\t\t" + return_statement

        s += "\n\t}"

        return s


def get_natives_func_from_natives_hpp_file(natives_hpp):
    functions_per_namespaces = {}
    current_namespace = ""
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
        elif "FORCEINLINE constexpr" in line:
            line = line.replace("FORCEINLINE constexpr", "")
            words = line.split()

            # remove NATIVE_DECL from the words array
            words.pop(0)

            func_name = ""
            for word in words:
                if "(" in word:
                    if func_name == "":
                        func_name = word.split("(")[0]

                    continue

            # Sol somehow choke on this, terrible software
            if func_name == "DRAW_TEXTURED_POLY_WITH_THREE_COLOURS":
                continue

            args = []
            args_start = line.split("(")[1]
            if args_start[0] == ")":
                # no args
                pass
            else:
                args_str = args_start.split(")")[0]
                i = 0
                for arg in args_str.split(","):
                    arg_type = arg[: arg.rfind(" ")].strip()
                    arg_name = arg[arg.rfind(" ") :].strip()
                    args.append(Arg(arg_name, arg_type))
                    i += 1

            return_type = (
                line[: line.find(func_name)].replace("NATIVE_DECL", "").strip()
            )

            lua_name = func_name
            if lua_name.startswith('_'):
                lua_name = lua_name.removeprefix("_")
                lua_name = lua_name + "_"

            native_func = NativeFunc(current_namespace, lua_name, func_name, args, return_type)

            functions_per_namespaces[current_namespace].append(native_func)

    return functions_per_namespaces


functions_per_namespaces = get_natives_func_from_natives_hpp_file(natives_hpp)

def generate_native_binding_cpp_and_hpp_files(functions_per_namespaces):
    generated_function_name = "void init_native_binding(sol::state& L)"

    print_hpp("#pragma once")
    # print_hpp('#include "lua/sol.hpp"')
    print_hpp("")
    print_hpp("namespace lua::native")
    print_hpp("{")
    print_hpp("\t" + generated_function_name + ";")
    print_hpp("")
    for namespace_name, native_funcs in functions_per_namespaces.items():
        print_hpp("\t" + "void init_native_binding_" + namespace_name + "(sol::state& L);")
    print_hpp("}")

    print_cpp('#include "lua_native_binding.hpp"')
    print_cpp("")
    print_cpp("namespace lua::native")
    print_cpp("{")

    i = 0

    for namespace_name, native_funcs in functions_per_namespaces.items():


        file_name_cpp = "../src/lua/natives/lua_native_binding_" + namespace_name + ".cpp"
        if os.path.exists(file_name_cpp):
            os.remove(file_name_cpp)
        f = open(file_name_cpp, "a")

        file_buffer = ""


        file_buffer += '#include "lua_native_binding.hpp"\n'
        file_buffer += '#include "natives.hpp"\n'
        if namespace_name == "FIRE":
            file_buffer += '#include "util/explosion_anti_cheat_bypass.hpp"\n'
        file_buffer += "\n"
        file_buffer += "namespace lua::native\n"
        file_buffer += "{\n"

        for native_func in native_funcs:
            file_buffer += "\tstatic " + str(native_func) + "\n\n"

        file_buffer += "\t" + "void init_native_binding_" + namespace_name + "(sol::state& L)\n"
        file_buffer += "\t{\n"

        file_buffer +=  "\t\tauto " + namespace_name + ' = L["' + namespace_name + '"].get_or_create<sol::table>();\n'

        for native_func in native_funcs:
            i += 1
            file_buffer += "\t\t"+ namespace_name+ '.set_function("'+ native_func.lua_name+ '", '+ "LUA_NATIVE_"+ native_func.namespace+ "_"+ native_func.lua_name+ ");\n"

        file_buffer+= "\t}\n" 
        file_buffer+= "}\n"

        f.write(file_buffer)
        f.close()

    print_cpp("\t" + generated_function_name)
    print_cpp("\t{")

    for namespace_name, native_funcs in functions_per_namespaces.items():
        # call each binding functions inside generated_function_name

        print_cpp("\t\t" + "init_native_binding_" + namespace_name + "(L);")

    print_cpp("\t}")
    print_cpp("}")

    print(f"Wrote binding for {i} native functions")


generate_native_binding_cpp_and_hpp_files(functions_per_namespaces)

def write_cpp_code(cpp_print_buf):
    file_name = "../src/lua/natives/lua_native_binding.cpp"
    if os.path.exists(file_name):
        os.remove(file_name)
    f = open(file_name, "a")
    f.write(cpp_print_buf)
    f.close()


def write_hpp_code(hpp_print_buf):
    file_name = "../src/lua/natives/lua_native_binding.hpp"
    if os.path.exists(file_name):
        os.remove(file_name)
    f = open(file_name, "a")
    f.write(hpp_print_buf)
    f.close()

write_cpp_code(cpp_print_buf)
write_hpp_code(hpp_print_buf)

