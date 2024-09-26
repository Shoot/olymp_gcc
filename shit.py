import re

def replace_defines_in_cpp(file_path):
    content = ''
    with open(file_path, 'r') as file:
        for line in file.readlines():
            if not line.startswith('#define'):
                content += line
    content = re.sub(r'\bfo\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*\)',
                      r'for (ll \1=\2; \1 < \3; \1+=1)', content)

    content = re.sub(r'\bforr\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*\)',
                      r'for (ll \1=\2; \1 <= \3; \1+=1)', content)
    content = re.sub(r'\broff\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*\)',
                     r'for (ll \1=\2; \1 >= \3; \1-=1)', content)


    # Write the modified content to a new file
    output_file_path = file_path.replace('.cpp', '2.cpp')
    with open(output_file_path, 'w') as output_file:
        output_file.write(content)

    print(f"Replaced defines written to {output_file_path}")

# Example usage
replace_defines_in_cpp('good.cpp')
