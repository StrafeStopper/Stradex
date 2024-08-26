with open('settings/build_number.txt', 'r') as file:
    build_number = int(file.read())

build_number += 1

with open('settings/build_number.txt', 'w') as file:
    file.write(str(build_number))