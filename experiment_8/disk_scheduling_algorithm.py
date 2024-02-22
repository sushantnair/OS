from matplotlib import pyplot as plt
import math
NOC = 200
def FCFS(sequence, start):
    temp = sequence.copy()
    temp.insert(0, start)
    plt.rcParams['xtick.bottom'] = plt.rcParams['xtick.labelbottom'] = False
    plt.rcParams['xtick.top'] = plt.rcParams['xtick.labeltop'] = True
    size = len(temp)
    x = temp
    y = []
    headmovement = 0
    for i in range(0, size):
        y.append(-i)
        if i != (size - 1):
            headmovement += abs(temp[i] - temp[i+1])
    string = 'Headmovement = ' + str(headmovement) + ' cylinders'
    string2 = str(temp)
    plt.plot(x, y, color="red", markerfacecolor='black', marker='o', markersize=8, linewidth=2, label="FCFS")
    plt.ylim = (0, size)
    plt.xlim = (0, NOC)
    plt.yticks([])
    plt.title("First Come First Served (FCFS) Disk Scheduling Algorithm")
    plt.text(172.5, -8.85, string, horizontalalignment='center', verticalalignment='center', fontsize=12)
    plt.text(172.5, -9.5, string2, horizontalalignment='center', verticalalignment='center', fontsize=12)
    plt.show()
def SSTF(sequence, start):
    temp = sequence.copy()
    def next_in_sequence(seq, val):
        diff = 0
        min_diff = math.inf
        nextval = 0
        for i in range (0, len(seq)):
            if(seq[i] != val):
                diff = abs(seq[i] - val)
                if(diff < min_diff):
                    min_diff = diff
                    nextval = seq[i]
        return nextval
    temp.insert(0, start)
    val = start
    x = []
    y = []
    size = 0
    x.append(start)
    headmovement = 0
    while(len(temp)):
        val = next_in_sequence(temp, val)
        x.append(val)
        temp.remove(val)
    size = len(x)
    for i in range(0, size):
        y.append(-i)
        if i != (size - 1):
            headmovement += abs(x[i] - x[i + 1])
    string = 'Headmovement = ' + str(headmovement) + ' cylinders'
    string2 = str(x)
    plt.plot(x, y, color="red", markerfacecolor="black", marker="o", markersize=8, linewidth=2, label="SSTF")
    plt.ylim = (0, size)
    plt.xlim = (0, NOC)
    plt.yticks([])
    plt.title("Shortest Seek Time First (SSTF) Disk Scheduling Algorithm")
    plt.text(182.5, -10.85, string, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -11.5, string2, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.show()
    
def SCAN(sequence, start, direction):
    temp = sequence.copy()
    left = []
    right = []
    x = []
    y = []
    x_approx = []
    y_approx = []
    headmovement = 0
    headmovement_approx = 0
    x.append(start)
    if(direction == "Left"):
        for i in temp:
            if i < start:
                left.append(i)
            else:
                right.append(i)
        left.sort(reverse = True)
        for i in left:
            x.append(i)
        x.append(0)
        right.sort()
        for i in right:
            x.append(i)
        x_approx.append(start)
        x_approx.append(min(x))
        x_approx.append(max(x))
        headmovement_approx = abs(start - 0)
        headmovement_approx += abs(0 - max(x))
    elif(direction == "Right"):
        for i in temp:
            if i > start:
                right.append(i)
            else:
                left.append(i)
        right.sort()
        for i in right:
            x.append(i)
        x.append(NOC)
        left.sort(reverse = True)
        for i in left:
            x.append(i)
        x_approx.append(start)
        x_approx.append(max(x))
        x_approx.append(min(x))
        headmovement_approx = abs(start - NOC)
        headmovement_approx += abs(NOC - min(x))
    y_approx.append(0)
    size = len(x)
    for i in range(0, size):
        y.append(-i)
        if(x[i] == 0 or x[i] == NOC):
            y_approx.append(-i)
        if i != (size - 1):
            headmovement += abs(x[i] - x[i + 1])
        else:
            y_approx.append(-i)
    string = 'Headmovement = ' + str(headmovement) + ' cylinders'
    string2 = str(x)
    string3 = 'Approximate Headmovement = ' + str(headmovement_approx) + ' cylinders'
    plt.plot(x, y, color="red", markerfacecolor="black", marker="o", markersize=8, linewidth=2, label="SCAN")
    plt.plot(x_approx, y_approx, dashes=[6, 2], color="green", markerfacecolor="white", marker="D", markersize=8, linewidth=0.5, label="Approximate SCAN")
    plt.ylim = (0, size)
    plt.xlim = (0, NOC)
    plt.yticks([])
    plt.title("SCAN Disk Scheduling Algorithm")
    plt.text(182.5, -10.85, string, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -12.5, string2, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -11.5, string3, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.show()

def CSCAN(sequence, start, direction):
    temp = sequence.copy()
    left = []
    right = []
    x = []
    y = []
    x_approx = []
    y_approx = []
    headmovement = 0
    headmovement_approx = 0
    x.append(start)
    if(direction == "Left"):
        for i in temp:
            if i < start:
                left.append(i)
            else:
                right.append(i)
        left.sort(reverse = True)
        for i in left:
            x.append(i)
        x.append(0)
        x.append(NOC)
        right.sort(reverse = True)
        for i in right:
            x.append(i)
        x_approx.append(start)
        x_approx.append(min(x))
        x_approx.append(max(x))
        x_approx.append(x[-1])
        headmovement_approx = abs(start - 0)
        headmovement_approx += abs(0 - max(x))
        headmovement_approx += abs(0 - x[-1])
    elif(direction == "Right"):
        for i in temp:
            if i > start:
                right.append(i)
            else:
                left.append(i)
        right.sort()
        for i in right:
            x.append(i)
        x.append(NOC)
        x.append(0)
        left.sort()
        for i in left:
            x.append(i)
        x_approx.append(start)
        x_approx.append(NOC)
        x_approx.append(0)
        x_approx.append(x[-1])
        headmovement_approx = abs(start - NOC)
        headmovement_approx += abs(NOC - 0)
        headmovement_approx += abs(0 - x[-1])
    y_approx.append(0)
    size = len(x)
    for i in range(0, size):
        y.append(-i)
        if(x[i] == 0 or x[i] == NOC):
            y_approx.append(-i)
        if i != (size - 1):
            headmovement += abs(x[i] - x[i + 1])
        else:
            y_approx.append(-i)
    string = 'Headmovement = ' + str(headmovement) + ' cylinders'
    string2 = str(x)
    string3 = 'Approximate Headmovement = ' + str(headmovement_approx) + ' cylinders'
    plt.plot(x, y, color="red", markerfacecolor="black", marker="o", markersize=8, linewidth=2, label="CSCAN")
    plt.plot(x_approx, y_approx, dashes=[6, 2], color="green", markerfacecolor="white", marker="D", markersize=8, linewidth=0.5, label="Approximate CSCAN")
    plt.ylim = (0, size)
    plt.xlim = (0, NOC)
    plt.yticks([])
    plt.title("CSCAN Disk Scheduling Algorithm")
    plt.text(182.5, -10.85, string, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -12.5, string2, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -11.5, string3, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.show()

def LOOK(sequence, start, direction):
    temp = sequence.copy()
    left = []
    right = []
    x = []
    y = []
    x_approx = []
    y_approx = []
    headmovement = 0
    headmovement_approx = 0
    x.append(start)
    if(direction == "Left"):
        for i in temp:
            if i < start:
                left.append(i)
            else:
                right.append(i)
        left.sort(reverse = True)
        for i in left:
            x.append(i)
        right.sort()
        for i in right:
            x.append(i)
        x_approx.append(start)
        x_approx.append(min(x))
        x_approx.append(max(x))
        headmovement_approx = abs(start - min(x))
        headmovement_approx += abs(min(x) - max(x))
    elif(direction == "Right"):
        for i in temp:
            if i > start:
                right.append(i)
            else:
                left.append(i)
        right.sort()
        for i in right:
            x.append(i)
        left.sort(reverse = True)
        for i in left:
            x.append(i)
        x_approx.append(start)
        x_approx.append(max(x))
        x_approx.append(min(x))
        headmovement_approx = abs(start - max(x))
        headmovement_approx += abs(max(x) - min(x))
    y_approx.append(0)
    size = len(x)
    for i in range(0, size):
        y.append(-i)
        if((x[i] == max(x) or x[i] == min(x)) and (i != size)):
            y_approx.append(-i)
        if i != (size - 1):
            headmovement += abs(x[i] - x[i + 1])
    string = 'Headmovement = ' + str(headmovement) + ' cylinders'
    string2 = str(x)
    string3 = 'Approximate Headmovement = ' + str(headmovement_approx) + ' cylinders'
    plt.plot(x, y, color="red", markerfacecolor="black", marker="o", markersize=8, linewidth=2, label="LOOK")
    plt.plot(x_approx, y_approx, dashes=[6, 2], color="green", markerfacecolor="white", marker="D", markersize=8, linewidth=0.5, label="Approximate LOOK")
    plt.ylim = (0, size)
    plt.xlim = (0, NOC)
    plt.yticks([])
    plt.title("LOOK Disk Scheduling Algorithm")
    plt.text(182.5, -10.85, string, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -12.5, string2, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -11.5, string3, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.show()

def CLOOK(sequence, start, direction):
    temp = sequence.copy()
    left = []
    right = []
    x = []
    y = []
    x_approx = []
    y_approx = []
    headmovement = 0
    headmovement_approx = 0
    x.append(start)
    if(direction == "Left"):
        for i in temp:
            if i < start:
                left.append(i)
            else:
                right.append(i)
        left.sort(reverse = True)
        for i in left:
            x.append(i)
        right.sort(reverse = True)
        for i in right:
            x.append(i)
        x_approx.append(start)
        x_approx.append(min(x))
        x_approx.append(max(x))
        x_approx.append(x[-1])
        headmovement_approx = abs(start - min(x))
        headmovement_approx += abs(min(x) - max(x))
        headmovement_approx += abs(max(x) - x[-1])
    elif(direction == "Right"):
        for i in temp:
            if i > start:
                right.append(i)
            else:
                left.append(i)
        right.sort()
        for i in right:
            x.append(i)
        left.sort()
        for i in left:
            x.append(i)
        x_approx.append(start)
        x_approx.append(max(x))
        x_approx.append(min(x))
        x_approx.append(x[-1])
        headmovement_approx = abs(start - max(x))
        headmovement_approx += abs(max(x) - min(x))
        headmovement_approx += abs(max(x) - x[-1])
    y_approx.append(0)
    size = len(x)
    for i in range(0, size):
        y.append(-i)
        if((x[i] == max(x) or x[i] == min(x)) and (i != size)):
            y_approx.append(-i)
        if i != (size - 1):
            headmovement += abs(x[i] - x[i + 1])
        else:
            y_approx.append(-i)
    string = 'Headmovement = ' + str(headmovement) + ' cylinders'
    string2 = str(x)
    string3 = 'Approximate Headmovement = ' + str(headmovement_approx) + ' cylinders'
    plt.plot(x, y, color="red", markerfacecolor="black", marker="o", markersize=8, linewidth=2, label="CLOOK")
    plt.plot(x_approx, y_approx, dashes=[6, 2], color="green", markerfacecolor="white", marker="D", markersize=8, linewidth=0.5, label="Approximate CLOOK")
    plt.ylim = (0, size)
    plt.xlim = (0, NOC)
    plt.yticks([])
    plt.title("CLOOK Disk Scheduling Algorithm")
    plt.text(182.5, -10.85, string, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -12.5, string2, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.text(182.5, -11.5, string3, horizontalalignment="center", verticalalignment="center", fontsize=12)
    plt.show()

def main():
    print('----------------------------------------------------------')
    print('----------------DISK SCHEDULING ALGORITHMS----------------')
    print('----------------------------------------------------------')
    sequence_fcfs = []
    sequence_sstf = []
    sequence_scan = []
    sequence_cscan = []
    sequence_look = []
    sequence_clook = []
    while True:
        print('Enter\n0 for All Disk Scheduling Algorithms')
        print('1 for FCFS Disk Scheduling Algorithm')
        print('2 for SSTF Disk Scheduling Algorithm')
        print('3 for SCAN Disk Scheduling Algorithm')
        print('4 for CSCAN Disk Scheduling Algorithm')
        print('5 for LOOK Disk Scheduling Algorithm')
        print('6 for CLOOK Disk Scheduling Algorithm')
        ch_alg = int(input('Enter your choice: '))
        print('----------------------------------------------------------')
        if ch_alg == 0:
            print('Enter\n0 for Default Sequence and Start')
            print('1 for custom Sequence and Start')
            ch_val = int(input('Enter your choice: '))
            if ch_val == 0:
                sequence_fcfs = [82, 170, 43, 140, 24, 16, 190]
                start_fcfs = 50
                sequence_sstf = sequence_fcfs
                start_sstf = start_fcfs
                sequence_scan = [93, 176, 42, 148, 27, 14, 180]
                start_scan = 55
                sequence_cscan = sequence_scan
                start_cscan = start_scan
                sequence_look = sequence_scan
                start_look = start_scan
                sequence_clook = sequence_cscan
                start_clook = start_cscan
                direction = "Right"
            else:
                nos = int(input('Enter the number of sequence: '))
                for i in range(0, nos):
                    sequence = int(input(f'Enter sequence {i+1} for FCFS (press enter when done): '))
                    sequence_fcfs.append(sequence)
                start_fcfs = int(input('Enter start position of cylinder head for FCFS: '))
                print('Enter \'True\' if you want rest of values to be the same')
                print('Otherwise, enter \'False\'.')
                ch_val_cpy = bool(input('Enter your choice: '))
                if ch_val_cpy == True:
                    sequence_sstf = sequence_fcfs
                    sequence_scan = sequence_fcfs
                    sequence_cscan = sequence_fcfs
                    sequence_look = sequence_fcfs
                    sequence_clook = sequence_fcfs
                    start_sstf = start_fcfs
                    start_scan = start_fcfs
                    start_cscan = start_fcfs
                    start_look = start_fcfs
                    start_clook = start_fcfs
                    direction = "Right"
                else:
                    nos = int(input('Enter the number of sequence: '))
                    for i in range(0, nos):
                        sequence = int(input(f'Enter sequence {i+1} for FCFS (press enter when done): '))
                        sequence_sstf.append(sequence)
                    nos = int(input('Enter the number of sequence: '))
                    for i in range(0, nos):
                        sequence = int(input(f'Enter sequence {i+1} for SSTF (press enter when done): '))
                        sequence_sstf.append(sequence)
                        nos = int(input('Enter the number of sequence: '))
                    for i in range(0, nos):
                        sequence = int(input(f'Enter sequence {i+1} for SCAN (press enter when done): '))
                        sequence_scan.append(sequence)
                        nos = int(input('Enter the number of sequence: '))
                    for i in range(0, nos):
                        sequence = int(input(f'Enter sequence {i+1} for CSCAN (press enter when done): '))
                        sequence_cscan.append(sequence)
                        nos = int(input('Enter the number of sequence: '))
                    for i in range(0, nos):
                        sequence = int(input(f'Enter sequence {i+1} for LOOK (press enter when done): '))
                        sequence_look.append(sequence)
                    nos = int(input('Enter the number of sequence: '))
                    for i in range(0, nos):
                        sequence = int(input(f'Enter sequence {i+1} for CLOOK (press enter when done): '))
                        sequence_clook.append(sequence)
                    start_sstf = int(input('Enter start position of cylinder head for SSTF: '))
                    start_scan = int(input('Enter start position of cylinder head for SCAN: '))
                    start_cscan = int(input('Enter start position of cylinder head for CSCAN: '))
                    start_look = int(input('Enter start position of cylinder head for LOOK: '))
                    start_clook = int(input('Enter start position of cylinder head for CLOOK: '))
                    direction = input("Enter the direction (Left/Right): ")
            FCFS(sequence_fcfs, start_fcfs)
            SSTF(sequence_sstf, start_sstf)
            SCAN(sequence_scan, start_scan, direction)
            CSCAN(sequence_cscan, start_cscan, direction)
            LOOK(sequence_look, start_look, direction)
            CLOOK(sequence_clook, start_clook, direction)
        elif ch_alg == 1:
            print('Enter\n0 for Default Sequence and Start')
            print('1 for custom Sequence and Start')
            ch_val = int(input('Enter your choice: '))
            if ch_val == 0:
                sequence_fcfs = [82, 170, 43, 140, 24, 16, 190]
                start_fcfs = 50
            else:
                nos = int(input('Enter the number of sequence: '))
                for i in range(0, nos):
                    sequence = int(input(f'Enter sequence {i+1} for FCFS (press enter when done): '))
                    sequence_fcfs.append(sequence)
                start_fcfs = int(input('Enter start position of cylinder head for FCFS: '))
            FCFS(sequence_fcfs, start_fcfs)
        elif ch_alg == 2:
            print('Enter\n0 for Default Sequence and Start')
            print('1 for custom Sequence and Start')
            ch_val = int(input('Enter your choice: '))
            if ch_val == 0:
                sequence_sstf = [82, 170, 43, 140, 24, 16, 190]
                start_sstf = 50
            else:
                nos = int(input('Enter the number of sequence: '))
                for i in range(0, nos):
                    sequence = int(input(f'Enter sequence {i+1} for SSTF (press enter when done): '))
                    sequence_sstf.append(sequence)
                start_sstf = int(input('Enter start position of cylinder head for SSTF: '))
            SSTF(sequence_sstf, start_sstf)
        elif ch_alg == 3:
            print('Enter\n0 for Default Sequence and Start')
            print('1 for custom Sequence and Start')
            ch_val = int(input('Enter your choice: '))
            if ch_val == 0:
                sequence_scan = [93, 176, 42, 148, 27, 14, 180]
                start_scan = 55
                direction = "Right"
            else:
                nos = int(input('Enter the number of sequence: '))
                for i in range(0, nos):
                    sequence = int(input(f'Enter sequence {i+1} for SCAN (press enter when done): '))
                    sequence_scan.append(sequence)
                start_scan = int(input('Enter start position of cylinder head for SCAN: '))
                direction = input("Enter the direction (Left/Right): ")
            SCAN(sequence_scan, start_scan, direction)
        elif ch_alg == 4:
            print('Enter\n0 for Default Sequence and Start')
            print('1 for custom Sequence and Start')
            ch_val = int(input('Enter your choice: '))
            if ch_val == 0:
                sequence_cscan = [93, 176, 42, 148, 27, 14, 180]
                start_cscan = 55
                direction = "Right"
            else:
                nos = int(input('Enter the number of sequence: '))
                for i in range(0, nos):
                    sequence = int(input(f'Enter sequence {i+1} for CSCAN (press enter when done): '))
                    sequence_cscan.append(sequence)
                start_cscan = int(input('Enter start position of cylinder head for CSCAN: '))
                direction = input("Enter the direction (Left/Right): ")
            CSCAN(sequence_cscan, start_cscan, direction)
        elif ch_alg == 5:
            print('Enter\n0 for Default Sequence and Start')
            print('1 for custom Sequence and Start')
            ch_val = int(input('Enter your choice: '))
            if ch_val == 0:
                sequence_look = [93, 176, 42, 148, 27, 14, 180]
                start_look = 55
                direction = "Right"
            else:
                nos = int(input('Enter the number of sequence: '))
                for i in range(0, nos):
                    sequence = int(input(f'Enter sequence {i+1} for LOOK (press enter when done): '))
                    sequence_look.append(sequence)
                start_look = int(input('Enter start position of cylinder head for LOOK: '))
                direction = input("Enter the direction (Left/Right): ")
            LOOK(sequence_look, start_look, direction)
        elif ch_alg == 6:
            print('Enter\n0 for Default Sequence and Start')
            print('1 for custom Sequence and Start')
            ch_val = int(input('Enter your choice: '))
            if ch_val == 0:
                sequence_clook = [93, 176, 42, 148, 27, 14, 180]
                start_clook = 55
                direction = "Right"
            else:
                nos = int(input('Enter the number of sequence: '))
                for i in range(0, nos):
                    sequence = int(input(f'Enter sequence {i+1} for CLOOK (press enter when done): '))
                    sequence_clook.append(sequence)
                start_clook = int(input('Enter start position of cylinder head for CLOOK: '))
                direction = input("Enter the direction (Left/Right): ")
            CLOOK(sequence_clook, start_clook, direction)
        ch_cont = input('Hit enter key to exit, otherwise press any character: ')
        if len(ch_cont) < 1:
            break
    print('----------------------------------------------------------')
    print('----------------------------------------------------------')
    print('----------------------------------------------------------')
if __name__ == "__main__":
    main()