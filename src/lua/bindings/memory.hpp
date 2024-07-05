#pragma once
#include "hooking/detour_hook.hpp"
#include "lua/lua_module.hpp"

#include <asmjit/asmjit.h>

namespace lua::memory
{
	enum type_info_t
	{
		none_,
		boolean_,
		string_,
		integer_,
		ptr_,
		float_,
		double_
	};

	// Lua API: Class
	// Name: pointer
	// Class representing a 64-bit memory address.

	struct pointer
	{
	private:
		uint64_t m_address;

	public:
		// Lua API: Constructor
		// Class: pointer
		// Param: address: integer: Address
		// Returns a memory instance, with the given address.
		explicit pointer(uint64_t address);

		explicit pointer();

		// Lua API: Function
		// Class: pointer
		// Name: add
		// Param: offset: integer: offset
		// Returns: pointer: new pointer object.
		// Adds an offset to the current memory address and returns a new pointer object.
		pointer add(uint64_t offset);

		// Lua API: Function
		// Class: pointer
		// Name: sub
		// Param: offset: integer: offset
		// Returns: pointer: new pointer object.
		// Subs an offset to the current memory address and returns a new pointer object.
		pointer sub(uint64_t offset);

		// Lua API: Function
		// Class: pointer
		// Name: rip
		// Param: offset: integer: offset
		// Returns: pointer: new pointer object.
		// Rips the current memory address and returns a new pointer object.
		pointer rip();

		// Lua API: Function
		// Class: pointer
		// Name: get_byte
		// Returns: number: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		// Lua API: Function
		// Class: pointer
		// Name: get_word
		// Returns: number: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		// Lua API: Function
		// Class: pointer
		// Name: get_dword
		// Returns: number: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		// Lua API: Function
		// Class: pointer
		// Name: get_float
		// Returns: float: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		// Lua API: Function
		// Class: pointer
		// Name: get_qword
		// Returns: number: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		template<typename T>
		T get()
		{
			return *(T*)m_address;
		}

		// Lua API: Function
		// Class: pointer
		// Name: set_byte
		// Param: value: number: new value.
		// Sets the value at the memory address to the specified value of the given type.

		// Lua API: Function
		// Class: pointer
		// Name: set_word
		// Param: value: number: new value.
		// Sets the value at the memory address to the specified value of the given type.

		// Lua API: Function
		// Class: pointer
		// Name: set_dword
		// Param: value: number: new value.
		// Sets the value at the memory address to the specified value of the given type.

		// Lua API: Function
		// Class: pointer
		// Name: set_float
		// Param: value: float: new value.
		// Sets the value at the memory address to the specified value of the given type.

		// Lua API: Function
		// Class: pointer
		// Name: set_qword
		// Param: value: number: new value.
		// Sets the value at the memory address to the specified value of the given type.

		template<typename T>
		void set(T value)
		{
			*(T*)m_address = value;
		}

		// Lua API: Function
		// Class: pointer
		// Name: get_string
		// Returns: string: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.
		std::string get_string();

		// Lua API: Function
		// Class: pointer
		// Name: set_string
		// Param: value: string: new value.
		// Sets the value at the memory address to the specified value of the given type.
		void set_string(const std::string& string, int max_length);

		// Lua API: Function
		// Class: pointer
		// Name: patch_byte
		// Param: value: number: new value.
		// Returns: lua_patch: memory patch instance for modifying the value at the memory address with the specified value. Can call apply / restore on the object.
		// Creates a memory patch for modifying the value at the memory address with the specified value.
		// The modified value is applied when you call the apply function on the lua_patch object.
		// The original value is restored when you call the restore function on the lua_patch object.

		// Lua API: Function
		// Class: pointer
		// Name: patch_word
		// Param: value: number: new value.
		// Returns: lua_patch: memory patch instance for modifying the value at the memory address with the specified value. Can call apply / restore on the object.
		// Creates a memory patch for modifying the value at the memory address with the specified value.
		// The modified value is applied when you call the apply function on the lua_patch object.
		// The original value is restored when you call the restore function on the lua_patch object.

		// Lua API: Function
		// Class: pointer
		// Name: patch_dword
		// Param: value: number: new value.
		// Returns: lua_patch: memory patch instance for modifying the value at the memory address with the specified value. Can call apply / restore on the object.
		// Creates a memory patch for modifying the value at the memory address with the specified value.
		// The modified value is applied when you call the apply function on the lua_patch object.
		// The original value is restored when you call the restore function on the lua_patch object.

		// Lua API: Function
		// Class: pointer
		// Name: patch_qword
		// Param: value: number: new value.
		// Returns: lua_patch: memory patch instance for modifying the value at the memory address with the specified value. Can call apply / restore on the object.
		// Creates a memory patch for modifying the value at the memory address with the specified value.
		// The modified value is applied when you call the apply function on the lua_patch object.
		// The original value is restored when you call the restore function on the lua_patch object.

		template<typename T>
		big::lua_patch* patch(T value, sol::this_state state)
		{
			big::lua_module* module = sol::state_view(state)["!this"];

			auto patch = std::make_unique<big::lua_patch>(::memory::byte_patch::make((T*)m_address, value).get());
			auto raw   = patch.get();
			module->m_registered_patches.push_back(std::move(patch));
			return raw;
		}

		// Lua API: Function
		// Class: pointer
		// Name: is_null
		// Returns: boolean: Returns true if the address is null.
		bool is_null();

		// Lua API: Function
		// Class: pointer
		// Name: is_valid
		// Returns: boolean: Returns true if the address is not null.
		bool is_valid();

		// Lua API: Function
		// Class: pointer
		// Name: deref
		// Returns: pointer: A new pointer object pointing to the value at that address.
		// Dereferences the memory address and returns a new pointer object pointing to the value at that address.
		pointer deref();

		// Lua API: Function
		// Class: pointer
		// Name: get_address
		// Returns: number: The memory address stored in the pointer object as a number.
		// Retrieves the memory address stored in the pointer object.
		uint64_t get_address() const;
	};

	class runtime_func_t
	{
		std::vector<uint8_t> m_jit_function_buffer;
		asmjit::x86::Mem m_args_stack;

		std::unique_ptr<big::detour_hook> m_detour;

	public:
		type_info_t m_return_type;
		std::vector<type_info_t> m_param_types;

		struct parameters_t
		{
			template<typename T>
			void set(const uint8_t idx, const T val) const
			{
				*(T*)get_arg_ptr(idx) = val;
			}

			template<typename T>
			T get(const uint8_t idx) const
			{
				return *(T*)get_arg_ptr(idx);
			}

			// asm depends on this specific type
			// we the runtime_func allocates stack space that is set to point here (check asmjit::compiler.newStack calls)
			volatile uintptr_t m_arguments;

			// must be char* for aliasing rules to work when reading back out
			char* get_arg_ptr(const uint8_t idx) const
			{
				return ((char*)&m_arguments) + sizeof(uintptr_t) * idx;
			}
		};

		class return_value_t
		{
			uintptr_t m_return_value;

		public:
			unsigned char* get() const
			{
				return (unsigned char*)&m_return_value;
			}
		};

		typedef bool (*user_pre_callback_t)(const parameters_t* params, const uint8_t parameters_count, return_value_t* return_value, const uintptr_t target_func_ptr);
		typedef void (*user_post_callback_t)(const parameters_t* params, const uint8_t parameters_count, return_value_t* return_value, const uintptr_t target_func_ptr);

		runtime_func_t()
		{
			m_detour      = std::make_unique<big::detour_hook>();
			m_return_type = type_info_t::none_;
		}

		~runtime_func_t()
		{
		}

		// Construct a callback given the raw signature at runtime. 'Callback' param is the C stub to transfer to,
		// where parameters can be modified through a structure which is written back to the parameter slots depending
		// on calling convention.
		uintptr_t make_jit_func(const asmjit::FuncSignature& sig, const asmjit::Arch arch, const user_pre_callback_t pre_callback, const user_post_callback_t post_callback, const uintptr_t target_func_ptr)
		{
			asmjit::CodeHolder code;
			auto env = asmjit::Environment::host();
			env.setArch(arch);
			code.init(env);

			// initialize function
			asmjit::x86::Compiler cc(&code);
			asmjit::FuncNode* func = cc.addFunc(sig);

			asmjit::StringLogger log;
			// clang-format off
			const auto format_flags =
				asmjit::FormatFlags::kMachineCode | asmjit::FormatFlags::kExplainImms | asmjit::FormatFlags::kRegCasts |
				asmjit::FormatFlags::kHexImms     | asmjit::FormatFlags::kHexOffsets  | asmjit::FormatFlags::kPositions;
			// clang-format on

			log.addFlags(format_flags);
			code.setLogger(&log);

			// too small to really need it
			func->frame().resetPreservedFP();

			// map argument slots to registers, following abi.
			std::vector<asmjit::x86::Reg> arg_registers;
			for (uint8_t arg_index = 0; arg_index < sig.argCount(); arg_index++)
			{
				const auto arg_type = sig.args()[arg_index];

				asmjit::x86::Reg arg;
				if (is_general_register(arg_type))
				{
					arg = cc.newUIntPtr();
				}
				else if (is_XMM_register(arg_type))
				{
					arg = cc.newXmm();
				}
				else
				{
					LOG(FATAL) << "Parameters wider than 64bits not supported";
					return 0;
				}

				func->setArg(arg_index, arg);
				arg_registers.push_back(arg);
			}

			// setup the stack structure to hold arguments for user callback
			uint32_t stack_size = (uint32_t)(sizeof(uintptr_t) * sig.argCount());
			m_args_stack        = cc.newStack(stack_size, 16);
			asmjit::x86::Mem args_stack_index(m_args_stack);

			// assigns some register as index reg
			asmjit::x86::Gp i = cc.newUIntPtr();

			// stack_index <- stack[i].
			args_stack_index.setIndex(i);

			// r/w are sizeof(uintptr_t) width now
			args_stack_index.setSize(sizeof(uintptr_t));

			// set i = 0
			cc.mov(i, 0);
			// mov from arguments registers into the stack structure
			for (uint8_t argIdx = 0; argIdx < sig.argCount(); argIdx++)
			{
				const auto argType = sig.args()[argIdx];

				// have to cast back to explicit register types to gen right mov type
				if (is_general_register(argType))
				{
					cc.mov(args_stack_index, arg_registers.at(argIdx).as<asmjit::x86::Gp>());
				}
				else if (is_XMM_register(argType))
				{
					cc.movq(args_stack_index, arg_registers.at(argIdx).as<asmjit::x86::Xmm>());
				}
				else
				{
					LOG(FATAL) << "Parameters wider than 64bits not supported";
					return 0;
				}

				// next structure slot (+= sizeof(uintptr_t))
				cc.add(i, sizeof(uintptr_t));
			}

			// get pointer to stack structure and pass it to the user pre callback
			asmjit::x86::Gp arg_struct = cc.newUIntPtr("arg_struct");
			cc.lea(arg_struct, m_args_stack);

			// fill reg to pass struct arg count to callback
			asmjit::x86::Gp arg_param_count = cc.newUInt8();
			cc.mov(arg_param_count, (uint8_t)sig.argCount());

			// create buffer for ret val
			asmjit::x86::Mem return_stack = cc.newStack(sizeof(uintptr_t), 16);
			asmjit::x86::Gp return_struct = cc.newUIntPtr("return_struct");
			cc.lea(return_struct, return_stack);

			// fill reg to pass target function pointer to callback
			asmjit::x86::Gp target_func_ptr_reg = cc.newUIntPtr();
			cc.mov(target_func_ptr_reg, target_func_ptr);

			asmjit::Label original_invoke_label      = cc.newLabel();
			asmjit::Label skip_original_invoke_label = cc.newLabel();

			// invoke the user pre callback
			asmjit::InvokeNode* pre_callback_invoke_node;
			cc.invoke(&pre_callback_invoke_node, (uintptr_t)pre_callback, asmjit::FuncSignatureT<bool, parameters_t*, uint8_t, return_value_t*, uintptr_t>());

			// call to user provided function (use ABI of host compiler)
			pre_callback_invoke_node->setArg(0, arg_struct);
			pre_callback_invoke_node->setArg(1, arg_param_count);
			pre_callback_invoke_node->setArg(2, return_struct);
			pre_callback_invoke_node->setArg(3, target_func_ptr_reg);

			// create a register for the user pre callback's return value
			// Note: the size of the register is important for the test instruction. newUInt8 since the pre callback returns a bool.
			asmjit::x86::Gp pre_callback_return_val = cc.newUInt8("pre_callback_return_val");
			// store the callback return value
			pre_callback_invoke_node->setRet(0, pre_callback_return_val);

			// if the callback return value is zero, skip orig.
			cc.test(pre_callback_return_val, pre_callback_return_val);
			cc.jz(skip_original_invoke_label);

			// label to invoke the original function
			cc.bind(original_invoke_label);

			// mov from arguments stack structure into regs
			cc.mov(i, 0); // reset idx
			for (uint8_t arg_idx = 0; arg_idx < sig.argCount(); arg_idx++)
			{
				const auto argType = sig.args()[arg_idx];

				if (is_general_register(argType))
				{
					cc.mov(arg_registers.at(arg_idx).as<asmjit::x86::Gp>(), args_stack_index);
				}
				else if (is_XMM_register(argType))
				{
					cc.movq(arg_registers.at(arg_idx).as<asmjit::x86::Xmm>(), args_stack_index);
				}
				else
				{
					LOG(FATAL) << "Parameters wider than 64bits not supported";
					return 0;
				}

				// next structure slot (+= sizeof(uint64_t))
				cc.add(i, sizeof(uint64_t));
			}

			// deref the trampoline ptr (holder must live longer, must be concrete reg since push later)
			asmjit::x86::Gp original_ptr = cc.zbx();
			cc.mov(original_ptr, m_detour->get_original_ptr());
			cc.mov(original_ptr, asmjit::x86::ptr(original_ptr));

			asmjit::InvokeNode* original_invoke_node;
			cc.invoke(&original_invoke_node, original_ptr, sig);
			for (uint8_t arg_index = 0; arg_index < sig.argCount(); arg_index++)
			{
				original_invoke_node->setArg(arg_index, arg_registers.at(arg_index));
			}

			if (sig.hasRet())
			{
				if (is_general_register(sig.ret()))
				{
					asmjit::x86::Gp tmp = cc.newUIntPtr();
					original_invoke_node->setRet(0, tmp);
					cc.mov(return_stack, tmp);
				}
				else
				{
					asmjit::x86::Xmm tmp = cc.newXmm();
					original_invoke_node->setRet(0, tmp);
					cc.movq(return_stack, tmp);
				}
			}

			cc.bind(skip_original_invoke_label);

			asmjit::InvokeNode* post_callback_invoke_node;
			cc.invoke(&post_callback_invoke_node, (uintptr_t)post_callback, asmjit::FuncSignatureT<void, parameters_t*, uint8_t, return_value_t*, uintptr_t>());

			// Set arguments for the post callback
			post_callback_invoke_node->setArg(0, arg_struct);
			post_callback_invoke_node->setArg(1, arg_param_count);
			post_callback_invoke_node->setArg(2, return_struct);
			post_callback_invoke_node->setArg(3, target_func_ptr_reg);

			if (sig.hasRet())
			{
				asmjit::x86::Mem return_stack_index(return_stack);
				return_stack_index.setSize(sizeof(uintptr_t));
				if (is_general_register(sig.ret()))
				{
					asmjit::x86::Gp tmp2 = cc.newUIntPtr();
					cc.mov(tmp2, return_stack_index);
					cc.ret(tmp2);
				}
				else
				{
					asmjit::x86::Xmm tmp2 = cc.newXmm();
					cc.movq(tmp2, return_stack_index);
					cc.ret(tmp2);
				}
			}

			cc.endFunc();

			// write to buffer
			cc.finalize();

			// worst case, overestimates for case trampolines needed
			code.flatten();
			size_t size = code.codeSize();

			// Allocate a virtual memory (executable).
			m_jit_function_buffer.reserve(size);

			DWORD old_protect;
			VirtualProtect(m_jit_function_buffer.data(), size, PAGE_EXECUTE_READWRITE, &old_protect);

			// if multiple sections, resolve linkage (1 atm)
			if (code.hasUnresolvedLinks())
			{
				code.resolveUnresolvedLinks();
			}

			// Relocate to the base-address of the allocated memory.
			code.relocateToBase((uintptr_t)m_jit_function_buffer.data());
			code.copyFlattenedData(m_jit_function_buffer.data(), size);

			LOG(VERBOSE) << "JIT Stub: " << log.data();

			return (uintptr_t)m_jit_function_buffer.data();
		}

		// Construct a callback given the typedef as a string. Types are any valid C/C++ data type (basic types), and pointers to
		// anything are just a uintptr_t. Calling convention is defaulted to whatever is typical for the compiler you use, you can override with
		// stdcall, fastcall, or cdecl (cdecl is default on x86). On x64 those map to the same thing.
		uintptr_t make_jit_func(const std::string& return_type, const std::vector<std::string>& param_types, const asmjit::Arch arch, const user_pre_callback_t pre_callback, const user_post_callback_t post_callback, const uintptr_t target_func_ptr, std::string call_convention = "")
		{
			auto get_type_info_from_string = [](const std::string& s) {
				if ((s.contains("const") && s.contains("char") && s.contains("*")) || s.contains("string"))
				{
					return type_info_t::string_;
				}
				else if (s.contains("bool"))
				{
					return type_info_t::boolean_;
				}
				else if (s.contains("ptr") || s.contains("pointer") || s.contains("*"))
				{
					// passing lua::memory::pointer
					return type_info_t::ptr_;
				}
				else if (s.contains("float"))
				{
					return type_info_t::float_;
				}
				else if (s.contains("double"))
				{
					return type_info_t::double_;
				}
				else
				{
					return type_info_t::integer_;
				}
			};

			m_return_type = get_type_info_from_string(return_type);

			asmjit::FuncSignature sig(get_call_convention(call_convention), asmjit::FuncSignature::kNoVarArgs, get_type_id(return_type));

			for (const std::string& s : param_types)
			{
				sig.addArg(get_type_id(s));
				m_param_types.push_back(get_type_info_from_string(s));
			}

			return make_jit_func(sig, arch, pre_callback, post_callback, target_func_ptr);
		}

		void create_and_enable_hook(const std::string& hook_name, uintptr_t target_func_ptr, uintptr_t jitted_func_ptr)
		{
			m_detour->set_instance(hook_name, (void*)target_func_ptr, (void*)jitted_func_ptr);

			m_detour->enable();
		}

	private:
		// does a given type fit in a general purpose register (i.e. is it integer type)
		bool is_general_register(const asmjit::TypeId type_id) const
		{
			switch (type_id)
			{
			case asmjit::TypeId::kInt8:
			case asmjit::TypeId::kUInt8:
			case asmjit::TypeId::kInt16:
			case asmjit::TypeId::kUInt16:
			case asmjit::TypeId::kInt32:
			case asmjit::TypeId::kUInt32:
			case asmjit::TypeId::kInt64:
			case asmjit::TypeId::kUInt64:
			case asmjit::TypeId::kIntPtr:
			case asmjit::TypeId::kUIntPtr: return true;
			default: return false;
			}
		}

		// float, double, simd128
		bool is_XMM_register(const asmjit::TypeId type_id) const
		{
			switch (type_id)
			{
			case asmjit::TypeId::kFloat32:
			case asmjit::TypeId::kFloat64: return true;
			default: return false;
			}
		}

		asmjit::CallConvId get_call_convention(const std::string& conv)
		{
			if (conv == "cdecl")
			{
				return asmjit::CallConvId::kCDecl;
			}
			else if (conv == "stdcall")
			{
				return asmjit::CallConvId::kStdCall;
			}
			else if (conv == "fastcall")
			{
				return asmjit::CallConvId::kFastCall;
			}

			return asmjit::CallConvId::kHost;
		}

		asmjit::TypeId get_type_id(const std::string& type)
		{
			if (type.find('*') != std::string::npos)
			{
				return asmjit::TypeId::kUIntPtr;
			}

#define TYPEID_MATCH_STR_IF(var, T)                                      \
	if (var == #T)                                                       \
	{                                                                    \
		return asmjit::TypeId(asmjit::TypeUtils::TypeIdOfT<T>::kTypeId); \
	}
#define TYPEID_MATCH_STR_ELSEIF(var, T)                                  \
	else if (var == #T)                                                  \
	{                                                                    \
		return asmjit::TypeId(asmjit::TypeUtils::TypeIdOfT<T>::kTypeId); \
	}

			TYPEID_MATCH_STR_IF(type, signed char)
			TYPEID_MATCH_STR_ELSEIF(type, unsigned char)
			TYPEID_MATCH_STR_ELSEIF(type, short)
			TYPEID_MATCH_STR_ELSEIF(type, unsigned short)
			TYPEID_MATCH_STR_ELSEIF(type, int)
			TYPEID_MATCH_STR_ELSEIF(type, unsigned int)
			TYPEID_MATCH_STR_ELSEIF(type, long)
			TYPEID_MATCH_STR_ELSEIF(type, unsigned long)
#ifdef POLYHOOK2_OS_WINDOWS
			TYPEID_MATCH_STR_ELSEIF(type, __int64)
			TYPEID_MATCH_STR_ELSEIF(type, unsigned __int64)
#endif
			TYPEID_MATCH_STR_ELSEIF(type, long long)
			TYPEID_MATCH_STR_ELSEIF(type, unsigned long long)
			TYPEID_MATCH_STR_ELSEIF(type, char)
			TYPEID_MATCH_STR_ELSEIF(type, char16_t)
			TYPEID_MATCH_STR_ELSEIF(type, char32_t)
			TYPEID_MATCH_STR_ELSEIF(type, wchar_t)
			TYPEID_MATCH_STR_ELSEIF(type, uint8_t)
			TYPEID_MATCH_STR_ELSEIF(type, int8_t)
			TYPEID_MATCH_STR_ELSEIF(type, uint16_t)
			TYPEID_MATCH_STR_ELSEIF(type, int16_t)
			TYPEID_MATCH_STR_ELSEIF(type, int32_t)
			TYPEID_MATCH_STR_ELSEIF(type, uint32_t)
			TYPEID_MATCH_STR_ELSEIF(type, uint64_t)
			TYPEID_MATCH_STR_ELSEIF(type, int64_t)
			TYPEID_MATCH_STR_ELSEIF(type, float)
			TYPEID_MATCH_STR_ELSEIF(type, double)
			TYPEID_MATCH_STR_ELSEIF(type, bool)
			TYPEID_MATCH_STR_ELSEIF(type, void)
			else if (type == "intptr_t")
			{
				return asmjit::TypeId::kIntPtr;
			}
			else if (type == "uintptr_t")
			{
				return asmjit::TypeId::kUIntPtr;
			}

			return asmjit::TypeId::kVoid;
		}
	};

	// Lua API: Class
	// Name: value_wrapper
	// Class for wrapping parameters and return value of functions, used mostly by the dynamic_hook system.

	class value_wrapper_t
	{
		char* m_value      = nullptr;
		type_info_t m_type = type_info_t::none_;

	public:
		value_wrapper_t(char* val, type_info_t type);

		// Lua API: Function
		// Class: value_wrapper
		// Name: get
		// Returns: any: The current value.
		// Get the value currently contained by the wrapper.
		sol::object get(sol::this_state state_);

		// Lua API: Function
		// Class: value_wrapper
		// Name: set
		// Param: new_value: any: The new value.
		// Set the new value contained by the wrapper.
		void set(sol::object new_val, sol::this_state state_);
	};

	void bind(sol::state& state);
}