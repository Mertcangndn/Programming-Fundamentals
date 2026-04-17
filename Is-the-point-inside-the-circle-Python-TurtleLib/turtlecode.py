# -*- coding: utf-8 -*-

import turtle

t=turtle.Turtle()
t.shape('circle')

form=turtle.Screen()
form.title('Question 4')

r=int(input("Çemberin Yarıçapını Giriniz: "))
x=int(input("Noktanın X Koordinatını Giriniz: "))
y=int(input("Noktanın Y Koordinatını Giriniz: "))

#İç-Dış Anlama İşlemi
dkare=x*x+y*y
rkare=r*r

if(dkare<=rkare):
    print("Nokta Dairenin İçinde")
else:
    print("Nokta Direnin Dışında")

#Turtle İşlemleri
t.penup()
t.right(90)
t.forward(r)
t.left(90)
t.pendown()
t.circle(r)

t.penup()
t.goto(x,y)
t.pendown()
t.begin_fill()
t.fillcolor('black')
t.circle(2)
t.end_fill()
t.hideturtle()
turtle.done()




