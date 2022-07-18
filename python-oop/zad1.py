import view_files


def read_file():
    path = input('Enter path: ')
    try:
        vc = view_files.ViewerCreator()
        viewer = vc.create_viewer(path)
        if isinstance(viewer, view_files.TextViewer):
            print(viewer.get_data())
        viewer.view()
    except Exception as e:
        print('Error: ' + str(e))
        print('Try again!')
        read_file()


def print_menu():
    print("=== CHOOSE ===")
    print("0. Exit")
    print("1. Read file")


if __name__ == '__main__':
    while True:
        print_menu()
        option = None
        try:
            option = int(input('Your choice: '))
        except Exception as e:
            print('Funny. It\'s not a number ')
            option = None
        match option:
            case 0:
                print('=== EXITING ===')
                exit(0)
            case 1:
                read_file()
            case _:
                print("Wrong option. Enter a number between 0 and 1.")

# txt: C:\Users\biumr\Desktop\tmp\avc.txt
# jpg: C:\Users\biumr\Desktop\tmp\img.jpg
