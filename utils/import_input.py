from pathlib import Path

# input folder name and user
ifn = "input"
usr = "mvp"

class DailyImput:
    def __init__(self):
        self.ifn = ifn
        self.usr = usr
        self.current_wd = Path().absolute()
        self.input_folder = self.current_wd.parent / ifn
        self.input_file = self.get_input_file_name()
    
    def get_input_file_name(self):
        day = self.input_folder.parent.name
        return f"{self.usr}_{day}.txt" # e.g. mvp_c01.txt

    def get_input(self, input_file=""):
        with open((self.input_folder / self.input_file), "r") as inp:
            file = inp.readlines()
        return file