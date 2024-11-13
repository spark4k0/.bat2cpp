import json
import re

def load_commands(config_file):
    with open(config_file, 'r', encoding='utf-8') as file:
        return file.read()
    
def escape_for_cpp(command):
    command = command.replace("\\", "\\\\")
    command = command.replace("\"", "\\\"")
    return command



def convert_to_cpp(commands):
    cpp_code = ""
    for command in commands.splitlines():
        command = command.strip()
        if not command or command.startswith("::") or command.startswith("echo") or command.startswith("@echo"):
            continue
        
        escaped_command = escape_for_cpp(command)
        cpp_code += f'    run_command("{escaped_command}");\n'
    
    return cpp_code


def write_cpp_file(cpp_code, output_file):
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(cpp_code)


def main():
    config_file = 'config.json'
    commands = load_commands(config_file)
    cpp_code = convert_to_cpp(commands)
    write_cpp_file(cpp_code, 'output.cpp')

if __name__ == "__main__":
    main()
