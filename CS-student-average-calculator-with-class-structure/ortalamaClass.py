# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt    #Import Plot library for crate tables

class Ogrenci():
    okul="<OKUL İSMİ>"                                                                                                  ###
    
    def __init__(self, isim, numara, bil111, bil103, mat101, imu021, imu011, bil121):
        self.numara=numara
        self.bil111=bil111
        self.bil103=bil103
        self.mat101=mat101
        self.imu021=imu021
        self.imu011=imu011
        self.isim=isim
        self.bil121=bil121
        
    def ort(self):
        sum=self.bil111+self.bil103+self.mat101+self.imu021+self.imu011
        ortalama=sum/5
        print("{} Adlı {} Numaralı Öğrencinin Ders Bazlı Ortalaması = {}".format(self.isim,self.numara,ortalama))

    def table(self):            #Bu kodu internet gelince dene.
        plt.bar(("bil111","bil103","mat101","imu021","imu011","bil121"),(self.bil111,self.bil103,self.mat101,self.imu021,self.imu011,self.bil121))
        
<NESNE İSMİ> = Ogrenci("isim", numara, bil111, bil103, mat101, imu021, imu011, bil121)                                  ###

<NESNE İSMİ>.ort()                                                                                                      ###
<NESNE İSMİ>.table()                                                                                                    ###

print(<NESNE İSMİ>.okul)     #Python nesne üzerinden class'a erişmeye izin verdiği için sorunsuz çalışacaktır,          ###
print(Ogrenci.okul)     #ancak başka IDE'ler için en doğru kullanum alttaki gibi olacaktır.
