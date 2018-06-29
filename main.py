import dane, subprocess, time, random
import _thread

tab = [100,150,200,250,300,350,400,450,500,550]
tab2 = [5,6,7,8,9,10,11,12,13,14,15]
results_files = ['wynik_euler.txt','wynik_hamilton.txt']
results = 'wynik_part2.txt'
data_files = ['dane_euler_'+str(i)+'_'+j+'.txt' for j in ['30','70'] for i in tab ]
data_2 = ['dane_czesc_2_'+str(i)+'.txt' for i in tab2]

def full(n):
    return n*(n-1)/2

def check(tab,percent):
    length = 0
    for i in tab:
        length += len(i) - 1
    n_max = full(max(tab[0])+1)
    if length > n_max * percent:
        return True
    return False

def count(tab):
    length = 0
    for i in tab:
        length += len(i) - 1
    n_max = full(max(tab[0])+1)
    return 100 * length/n_max

def fill(ile,procent):
    arr = [[0] + dane.los_bez_pow(ile) + [0]]
    while(not check(arr,procent*0.01)):
        boo = False
        a1,a2,a3 = random.sample(set(arr[0]),3)
        for i in arr:
            try:
                p1 = i.index(a1)
                p2 = i.index(a2)
                p3 = i.index(a3)
            except ValueError:
                pass
            if p1+1 == p2 or p1-1 == p2 or p1+1 == p3 or p1-1 == p3 or p2+1 == p3 or p2-1 == p3:
                boo = True
        while boo:
            boo = False
            a1,a2,a3 = random.sample(set(arr[0]),3)
            for i in arr:
                try:
                    p1 = i.index(a1)
                    p2 = i.index(a2)
                    p3 = i.index(a3)
                except ValueError:
                    pass
                if p1+1 == p2 or p1-1 == p2 or p1+1 == p3 or p1-1 == p3 or p2+1 == p3 or p2-1 == p3:
                    boo = True
        arr += [[a1,a2,a3,a1]]
    return arr

def timer(temp,delay):
    time.sleep(delay)
    print(temp)

def execution(task,time_period):
    # p1 = Process(target=timer,args=(time_period,''))
    # p2 = Process(target=timer,args=(2,''))
    # p1.start()
    # p2.start()
    try:
       _thread.start_new_thread( timer, ("Thread-1", 2, ) )
       _thread.start_new_thread( timer, ("Thread-2", 4, ) )
    except:
        print ("Error: unable to start thread")

def how_many(file):
    with open(file,'r') as f:
        tab = f.readline().split(' ')
    return [int(i) for i in tab if i != '']


def generowanie_danych():
    for i in data_files:
        # print(i)
        with open('dane/'+i,'w') as file:
            print('Processing: '+i,end=' ')
            tab = fill(int(i[11:i.index('_',12)]),int(i[-6:-4]))
            for j in tab:
                for k in j:
                    file.write(str(k)+' ')
            print(': Done')

def Main():
    for i in results_files:
        first_30 = True
        first_70 = True
        for file_name in data_files:
            if file_name[-6:-4] == '30' and first_30:
                first_30 = False
                with open(i,'a') as f:
                    f.write('\n30')
            if file_name[-6:-4] == '70' and first_70:
                first_70 = False
                with open(i,'a') as f:
                    f.write('\n70')
            print('[+] Executing: ',file_name[5:-4],end=' ')
            # args: 1 - {0(euler),1(hamilton),2(part2)} 2 - dane 3 - wynik
            p = how_many('dane/'+file_name)
            subprocess.run(['./main',str(results_files.index(i)),'dane/'+file_name,i,str(len(p)),str(max(p)+1)])
            # print(['./main',str(results_files.index(i)),'dane/'+file_name,i,str(len(p)),str(max(p)+1)])
            print('- Finished')
    first = True
    for i in data_2:
        print('[+] Executing: ',i[5:-4],end=' ')
        if first:
            first = False
            with open(results,'a') as f:
                f.write('\n50')
        p = how_many('dane/'+i)
        subprocess.run(['./main','2','dane/'+i,results,str(len(p)),str(max(p)+1)])
        # print(['./main','2','dane/'+i,results,str(len(p)),str(max(p)+1)])
        print('- Finished')

if __name__ == '__main__':
    Main()
