import pandas as pd

def MAXIMUM_PLANAR_SUBSET(C, N):
    exe_times = 0
    M = [[None] * (2*N) for i in range(2*N)]
    chosen_chord = [[None] * (2*N) for i in range(2*N)]
    for i in range(0, 2*N, 1):
        M[i][i] = 0
    for i in range(1, 2*N, 1):
        M[i][i-1] = 0
    # print(M)
    for l in range(1, 2*N, 1):
        for i in range(0, 2*N-l, 1):
            j = i + l
            k = C[j][1]
            # print(i, j, k)
            if k < i or k > j:
                M[i][j] = M[i][j-1]
            elif k == i:
                M[i][j] = M[i+1][j-1] + 1
                chosen_chord[i][j] = k
            else:
                if M[i][j-1] >= M[i][k-1] + 1 + M[k+1][j-1]:
                    M[i][j] = M[i][j-1]
                else:
                    M[i][j] = M[i][k-1] + 1 + M[k+1][j-1]
                    chosen_chord[i][j] = k
            exe_times += 1
    print(f'exe_times = {exe_times}')
    return M, chosen_chord

def readInputFile(path):
    with open(path, 'r') as f:
        N = int(f.readline().strip()) // 2
        C = []
        for line in f.readlines():
            if line.strip() == '0':
                break
            C.append(list(map(int, line.strip().split(' '))))
            C.append(C[-1][::-1])
    return N, sorted(C)

recursion_times = 0

def printChord(chosen_chord, i, j, file):
    global recursion_times
    recursion_times += 1
    if i >= j:
        return
    # i_current = i
    for j_current in range(j, i, -1):
        # if i_current == j_current:
        #     break
        k_current = chosen_chord[i][j_current]
        if k_current != None:
            printChord(chosen_chord, i, k_current-1, file)
            print(f'chord: {k_current}_{j_current}')
            file.write(f'{k_current} {j_current}\n')
            printChord(chosen_chord, k_current+1, j_current-1, file)
            break
    return
        


if __name__ == '__main__':
    file_name = '100000'
    N, C = readInputFile("inputs\\" + file_name + ".in")
    # print(f'N = {pd.DataFrame(N)}')
    # print(f'C = {pd.DataFrame(C)}')
    print(f'N = {N}')
    print(f'C = \n{pd.DataFrame(C)}')
    M, chosen_chord = MAXIMUM_PLANAR_SUBSET(C, N)
    print(f'M = \n{pd.DataFrame(M).astype(pd.Int32Dtype())}')
    print(f'chosen_chord = \n{pd.DataFrame(chosen_chord).astype(pd.Int32Dtype())}')
    print(f'Ans. = {M[0][2*N-1]}')

    with open("outputs\\my" + file_name + ".out", 'w') as f:
        f.write(f'{M[0][2*N-1]}\n')
        printChord(chosen_chord, 0, 2*N-1, f)
    print(f'recursion_times = {recursion_times}')