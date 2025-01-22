from subprocess import *

def sortuniq(inpfilepath, outfilepath):
    fp_in = open(inpfilepath, "r")
    fp_out = open(outfilepath, "w")

    p_sort = Popen(["/usr/bin/sort"], stdin=fp_in, stdout=PIPE)
    p_uniq = Popen(["/usr/bin/uniq"], stdin=p_sort.stdout, stdout=fp_out)

    p_sort.stdout.close()

    fp_in.close()
    fp_out.close()

    p_sort.wait()
    p_uniq.wait()


if __name__ == "__main__":
    sortuniq("input.txt", "output.txt")