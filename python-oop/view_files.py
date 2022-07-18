import mimetypes
import os
import re
import string
from abc import abstractmethod, ABC


class FileViewer(ABC):
    def __init__(self, path):
        self.path = path

    @abstractmethod
    def view(self):
        pass


class TextBuffer:
    def __init__(self):
        self.text: string = None

    def read_from_fime(self, path):
        with open(path) as file:
            self.text = file.read()


class TextStats:
    def __init__(self):
        self.number_of_lines = None
        self.number_of_words = None
        self.number_of_nonalpha = None

    def compute(self, text: string):
        self.number_of_lines = text.count('\n')
        self.number_of_words = len(text.split())
        self.number_of_nonalpha = len(re.findall(r'[^a-zA-Z0-9 ]', text))

    def __str__(self):
        return "lines: " + str(self.number_of_lines) + ", words: " + str(self.number_of_words) + ", nonalpha: " + str(
            self.number_of_nonalpha)


class TextViewer(FileViewer, TextBuffer):
    __test_stats: TextStats

    def __init__(self, path):
        FileViewer.__init__(self, path)
        TextBuffer.__init__(self)
        self.read_from_fime(path)
        self.__test_stats = TextStats()
        self.__test_stats.compute(self.text)

    def view(self):
        os.startfile(self.path)

    def get_data(self) -> TextStats:
        return self.__test_stats


class ImageViewer(FileViewer):
    def __init__(self, path):
        super().__init__(path)

    def view(self):
        os.startfile(self.path)


class ViewerCreator:
    def __init__(self):
        pass

    def create_viewer(self, path: string) -> FileViewer:
        return self._detect_viewer_type(path)(path)

    @staticmethod
    def _detect_viewer_type(path: string) -> type:
        match mimetypes.guess_type(path)[0]:
            case 'text/plain':
                return TextViewer
            case 'image/jpeg' | 'image/png':
                return ImageViewer
            case _:
                raise Exception('Mimetype not supported or file not found.')

# vc = ViewerCreator()
# viewer = vc.create_viewer("C:\\Users\\biumr\\Desktop\\tmp\\img.jpg")
# viewer.view()
