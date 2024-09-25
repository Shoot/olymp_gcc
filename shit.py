import re

def replace_defines_in_cpp(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    # Regex to match #define statements
    define_pattern = r'^\s*#define\s+(\w+)(\s+)(.*)$'

    # Dictionary to store defined macros
    defines = {}

    # Find all #define statements
    for match in re.finditer(define_pattern, content, re.MULTILINE):
        key = match.group(1)
        value = match.group(3).strip()
        defines[key] = value

    # Replace defines in the content
    for key, value in defines.items():
        # Handle replacements with quotes
        quoted_value = re.sub(r'(?<![a-zA-Z_])' + re.escape(key) + r'(?![a-zA-Z_])', value, content)
        content = quoted_value

    # Write the modified content to a new file
    output_file_path = file_path.replace('.cpp', '2.cpp')
    with open(output_file_path, 'w') as output_file:
        output_file.write(content)

    print(f"Replaced defines written to {output_file_path}")

# Example usage
replace_defines_in_cpp('sol.cpp')
