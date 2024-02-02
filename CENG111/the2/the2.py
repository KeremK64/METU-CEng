coordinates = eval(input())
area = 0

coordinates_x = [coordinates[0][0],coordinates[1][0],coordinates[2][0],coordinates[3][0]]
coordinates_y = [coordinates[0][1],coordinates[1][1],coordinates[2][1],coordinates[3][1]]

min_x = min(coordinates_x)
max_x = max(coordinates_x)



min_y = min(coordinates_y)
max_y = max(coordinates_y)




#Above the x-axis ones
        #CONDITION1
if(((min_x == coordinates_x[2] and coordinates_x[0] <= coordinates_x[3] <= coordinates_x[1]) and (max_y == coordinates_y[2] or max_y == coordinates_y[3])) ):
        if(min_y > 0):
                area += abs((coordinates_x[1] - coordinates_x[2])*abs(coordinates_y[2] - coordinates_y[1]))/2
        
                area += (coordinates_x[1] - coordinates_x[2]) * coordinates_y[1 if coordinates_y[2] > coordinates_y[1] else 2]
        else:
                area += abs(max_x-min_x)*abs(max_y)
        
                area += (abs(coordinates_x[3] - coordinates_x[2])) * (abs(coordinates_y[2] - coordinates_y[3])) /2
        
                area += abs(coordinates_x[3] - coordinates_x[1]) * abs(coordinates_y[3] - coordinates_y[1]) / 2
                
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[0]*coordinates_y[3] + coordinates_x[3]*coordinates_y[1] + coordinates_x[1]*coordinates_y[0] - coordinates_y[0]*coordinates_x[3] - coordinates_y[3]*coordinates_x[1] - coordinates_y[1]*coordinates_x[0]) / 2

if(((min_x == coordinates_x[1] and coordinates_x[3] <= coordinates_x[2] <= coordinates_x[0]) and (max_y == coordinates_y[1] or max_y == coordinates_y[2]))):
        if(min_y > 0):
                area += abs((coordinates_x[0] - coordinates_x[1])*abs(coordinates_y[1] - coordinates_y[0]))/2
                
                area += (coordinates_x[0] - coordinates_x[1]) * coordinates_y[0 if coordinates_y[1] > coordinates_y[0] else 1]
        else:
                area += abs(max_x-min_x)*abs(max_y)
                area += abs(coordinates_x[2] - coordinates_x[1]) * abs(coordinates_y[1] - coordinates_y[2])/2
                area += abs(coordinates_x[2] - coordinates_x[0]) * abs(coordinates_y[2] - coordinates_y[0]) / 2
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[3]*coordinates_y[2] + coordinates_x[2]*coordinates_y[0] + coordinates_x[0]*coordinates_y[3] - coordinates_y[3]*coordinates_x[2] - coordinates_y[2]*coordinates_x[0] - coordinates_y[0]*coordinates_x[3]) / 2


if(((min_x == coordinates_x[0] and coordinates_x[2] <= coordinates_x[1] <= coordinates_x[3]) and (max_y == coordinates_y[0] or max_y == coordinates_y[1]))):
        if(min_y > 0):
                area += abs((coordinates_x[3] - coordinates_x[0])*abs(coordinates_y[0] - coordinates_y[3]))/2
        
                area += (coordinates_x[3] - coordinates_x[0]) * coordinates_y[3 if coordinates_y[0] > coordinates_y[3] else 0]
        else:
                area += abs(max_x-min_x)*abs(max_y)
                area += abs(coordinates_x[1] - coordinates_x[0]) * abs(coordinates_y[0] - coordinates_y[1])/2
                area += abs(coordinates_x[1] - coordinates_x[3]) * abs(coordinates_y[1] - coordinates_y[3]) / 2
                
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[2]*coordinates_y[1] + coordinates_x[1]*coordinates_y[3] + coordinates_x[3]*coordinates_y[2] - coordinates_y[2]*coordinates_x[1] - coordinates_y[1]*coordinates_x[3] - coordinates_y[3]*coordinates_x[2]) / 2


if(((min_x == coordinates_x[3] and coordinates_x[1] <= coordinates_x[0] <= coordinates_x[2]) and (max_y == coordinates_y[0] or max_y == coordinates_y[3]))):
        if(min_y > 0):
                area += abs((coordinates_x[2] - coordinates_x[3])*abs(coordinates_y[3] - coordinates_y[2]))/2
        
                area += (coordinates_x[2] - coordinates_x[3]) * coordinates_y[2 if coordinates_y[3] > coordinates_y[2] else 3]
        else:
                area += abs(max_x-min_x)*abs(max_y)
                area += abs(coordinates_x[0] - coordinates_x[3]) * abs(coordinates_y[3] - coordinates_y[0])/2
                area += abs(coordinates_x[0] - coordinates_x[2]) * abs(coordinates_y[0] - coordinates_y[2]) / 2
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[1]*coordinates_y[0] + coordinates_x[0]*coordinates_y[2] + coordinates_x[2]*coordinates_y[1] - coordinates_y[1]*coordinates_x[0] - coordinates_y[0]*coordinates_x[2] - coordinates_y[2]*coordinates_x[1]) / 2

        #CONDITION3
if((max_x == coordinates_x[2] and coordinates_x[3] <= coordinates_x[1] <= coordinates_x[0]) and (max_y == coordinates_y[2] or max_y == coordinates_y[1])):
        if(min_y > 0):
                area += abs((coordinates_x[2] - coordinates_x[3])*abs(coordinates_y[2] - coordinates_y[3]))/2
        
                area += (coordinates_x[2] - coordinates_x[3]) * coordinates_y[2 if coordinates_y[3] > coordinates_y[2] else 3]
        else:
                area += abs(max_x-min_x)*abs(max_y)
                
                area += abs(coordinates_x[1] - coordinates_x[2]) * abs(coordinates_y[2] - coordinates_y[1]) /2
                
                area += abs(coordinates_x[3] - coordinates_x[1]) * abs(coordinates_y[3] - coordinates_y[1]) / 2
             
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[0]*coordinates_y[3] + coordinates_x[3]*coordinates_y[1] + coordinates_x[1]*coordinates_y[0] - coordinates_y[0]*coordinates_x[3] - coordinates_y[3]*coordinates_x[1] - coordinates_y[1]*coordinates_x[0]) / 2

if((max_x == coordinates_x[1] and coordinates_x[2] <= coordinates_x[0] <= coordinates_x[3]) and (max_y == coordinates_y[0] or max_y == coordinates_y[1])):
        if(min_y > 0):
                area += abs((coordinates_x[1] - coordinates_x[2])*abs(coordinates_y[1] - coordinates_y[2]))/2
        
                area += (coordinates_x[1] - coordinates_x[2]) * coordinates_y[1 if coordinates_y[2] > coordinates_y[1] else 2]
        else:
                area += abs(max_x-min_x)*abs(max_y)
                area += abs(coordinates_x[0] - coordinates_x[1]) * abs(coordinates_y[1] - coordinates_y[0])/2
                area += abs(coordinates_x[2] - coordinates_x[0]) * abs(coordinates_y[2] - coordinates_y[0]) / 2
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[3]*coordinates_y[2] + coordinates_x[2]*coordinates_y[0] + coordinates_x[0]*coordinates_y[3] - coordinates_y[3]*coordinates_x[2] - coordinates_y[2]*coordinates_x[0] - coordinates_y[0]*coordinates_x[3]) / 2

if((max_x == coordinates_x[0] and coordinates_x[1] <= coordinates_x[3] <= coordinates_x[2]) and (max_y == coordinates_y[3] or max_y == coordinates_y[0])):
        if(min_y > 0):
                area += abs((coordinates_x[0] - coordinates_x[1])*abs(coordinates_y[0] - coordinates_y[1]))/2
        
                area += (coordinates_x[0] - coordinates_x[1]) * coordinates_y[0 if coordinates_y[1] > coordinates_y[0] else 1]
        else:
                area += abs(max_x-min_x)*abs(max_y)
                area += abs(coordinates_x[3] - coordinates_x[0]) * abs(coordinates_y[0] - coordinates_y[3])/2
                area += abs(coordinates_x[1] - coordinates_x[3]) * abs(coordinates_y[1] - coordinates_y[3]) / 2
                
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[2]*coordinates_y[1] + coordinates_x[1]*coordinates_y[3] + coordinates_x[3]*coordinates_y[2] - coordinates_y[2]*coordinates_x[1] - coordinates_y[1]*coordinates_x[3] - coordinates_y[3]*coordinates_x[2]) / 2

if((max_x == coordinates_x[3] and coordinates_x[0] <= coordinates_x[2] <= coordinates_x[1]) and (max_y == coordinates_y[2] or max_y == coordinates_y[3])):
        if(min_y > 0):
                area += abs((coordinates_x[3] - coordinates_x[0])*abs(coordinates_y[3] - coordinates_y[2]))/2
        
                area += (coordinates_x[3] - coordinates_x[0]) * coordinates_y[3 if coordinates_y[0] > coordinates_y[3] else 0]
        else:
                area += abs(max_x-min_x)*abs(max_y)
                area += abs(coordinates_x[2] - coordinates_x[3]) * abs(coordinates_y[3] - coordinates_y[2])/2
                area += abs(coordinates_x[0] - coordinates_x[2]) * abs(coordinates_y[0] - coordinates_y[2]) / 2
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[1]*coordinates_y[0] + coordinates_x[0]*coordinates_y[2] + coordinates_x[2]*coordinates_y[1] - coordinates_y[1]*coordinates_x[0] - coordinates_y[0]*coordinates_x[2] - coordinates_y[2]*coordinates_x[1]) / 2 

        #CONDITION2

if((min_x == coordinates_x[2] and coordinates_x[0] <= coordinates_x[1] <= coordinates_x[3]) and (min_y == coordinates_y[1] or min_y == coordinates_y[2])):
        if(min_y > 0):
                area += abs(max_x-min_x)*abs(min_y)
                
                area += abs(coordinates_x[1] - coordinates_x[2]) * abs(coordinates_y[2] - coordinates_y[1]) /2
                
                area += abs(coordinates_x[3] - coordinates_x[1]) * abs(coordinates_y[3] - coordinates_y[1]) / 2

                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[0]*coordinates_y[3] + coordinates_x[3]*coordinates_y[1] + coordinates_x[1]*coordinates_y[0] - coordinates_y[0]*coordinates_x[3] - coordinates_y[3]*coordinates_x[1] - coordinates_y[1]*coordinates_x[0]) / 2
        else:
                area += abs((coordinates_x[2] - coordinates_x[3])*abs(coordinates_y[2] - coordinates_y[3]))/2
       
                area += (coordinates_x[2] - coordinates_x[3]) * abs(max_y)

if((min_x == coordinates_x[1] and coordinates_x[3] <= coordinates_x[0] <= coordinates_x[2]) and (abs(min_y) == abs(coordinates_y[1]) or abs(min_y) == abs(coordinates_y[0]))):
        if(min_y > 0):
                area += abs(max_x-min_x)*abs(min_y)
                area += abs(coordinates_x[0] - coordinates_x[1]) * abs(coordinates_y[1] - coordinates_y[0])/2
                area += abs(coordinates_x[2] - coordinates_x[0]) * abs(coordinates_y[2] - coordinates_y[0]) / 2
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[3]*coordinates_y[2] + coordinates_x[2]*coordinates_y[0] + coordinates_x[0]*coordinates_y[3] - coordinates_y[3]*coordinates_x[2] - coordinates_y[2]*coordinates_x[0] - coordinates_y[0]*coordinates_x[3]) / 2
        else:
                area += abs((coordinates_x[1] - coordinates_x[2])*abs(coordinates_y[1] - coordinates_y[2]))/2
       
                area += (coordinates_x[1] - coordinates_x[2]) * abs(max_y)
   
if((min_x == coordinates_x[0] and coordinates_x[2] <= coordinates_x[3] <= coordinates_x[1]) and (min_y == coordinates_y[0] or min_y == coordinates_y[3])):
        if(min_y > 0):
                area += abs(max_x-min_x)*abs(min_y)
                area += abs(coordinates_x[3] - coordinates_x[0]) * abs(coordinates_y[0] - coordinates_y[3])/2
                area += abs(coordinates_x[1] - coordinates_x[3]) * abs(coordinates_y[1] - coordinates_y[3]) / 2
                
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[2]*coordinates_y[1] + coordinates_x[1]*coordinates_y[3] + coordinates_x[3]*coordinates_y[2] - coordinates_y[2]*coordinates_x[1] - coordinates_y[1]*coordinates_x[3] - coordinates_y[3]*coordinates_x[2]) / 2
        else:
                area += abs((coordinates_x[0] - coordinates_x[1])*abs(coordinates_y[0] - coordinates_y[1]))/2
       
                area += (coordinates_x[0] - coordinates_x[1]) * abs(max_y)

if((min_x == coordinates_x[3] and coordinates_x[1] <= coordinates_x[2] <= coordinates_x[0]) and (min_y == coordinates_y[2] or min_y == coordinates_y[3])):
        if(min_y > 0):
                area += abs(max_x-min_x)*abs(min_y)
                area += abs(coordinates_x[2] - coordinates_x[3]) * abs(coordinates_y[3] - coordinates_y[2])/2
                area += abs(coordinates_x[0] - coordinates_x[2]) * abs(coordinates_y[0] - coordinates_y[2]) / 2
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[1]*coordinates_y[0] + coordinates_x[0]*coordinates_y[2] + coordinates_x[2]*coordinates_y[1] - coordinates_y[1]*coordinates_x[0] - coordinates_y[0]*coordinates_x[2] - coordinates_y[2]*coordinates_x[1]) / 2
        else:
                area += abs((coordinates_x[3] - coordinates_x[0])*abs(coordinates_y[3] - coordinates_y[2]))/2
       
                area += (coordinates_x[3] - coordinates_x[0]) * abs(max_y)

        #CONDITION4

if((max_x == coordinates_x[2] and coordinates_x[1] <= coordinates_x[3] <= coordinates_x[0]) and (min_y == coordinates_y[2] or min_y == coordinates_y[3])):
        if(min_y > 0):
                area += abs(max_x-min_x)*abs(min_y)
        
                area += (abs(coordinates_x[3] - coordinates_x[2])) * (abs(coordinates_y[2] - coordinates_y[3])) /2
        
                area += abs(coordinates_x[3] - coordinates_x[1]) * abs(coordinates_y[3] - coordinates_y[1]) / 2
        
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[0]*coordinates_y[3] + coordinates_x[3]*coordinates_y[1] + coordinates_x[1]*coordinates_y[0] - coordinates_y[0]*coordinates_x[3] - coordinates_y[3]*coordinates_x[1] - coordinates_y[1]*coordinates_x[0]) / 2
        else:
                area += abs((coordinates_x[1] - coordinates_x[2])*abs(coordinates_y[2] - coordinates_y[1]))/2
       
                area += abs(coordinates_x[1] - coordinates_x[2]) * abs(max_y)

if((max_x == coordinates_x[1] and coordinates_x[3] <= coordinates_x[0] <= coordinates_x[2]) and (min_y == coordinates_y[1] or min_y == coordinates_y[2])):
        if(min_y > 0):
                area += abs(max_x-min_x)*abs(min_y)
                area += abs(coordinates_x[2] - coordinates_x[1]) * abs(coordinates_y[1] - coordinates_y[2])/2
                area += abs(coordinates_x[2] - coordinates_x[0]) * abs(coordinates_y[2] - coordinates_y[0]) / 2
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[3]*coordinates_y[2] + coordinates_x[2]*coordinates_y[0] + coordinates_x[0]*coordinates_y[3] - coordinates_y[3]*coordinates_x[2] - coordinates_y[2]*coordinates_x[0] - coordinates_y[0]*coordinates_x[3]) / 2
        else:
                area += abs((coordinates_x[0] - coordinates_x[1])*abs(coordinates_y[1] - coordinates_y[0]))/2
        
                area += (coordinates_x[0] - coordinates_x[1]) * abs(max_y)

if((max_x == coordinates_x[0] and coordinates_x[2] <= coordinates_x[3] <= coordinates_x[1]) and (min_y == coordinates_y[0] or min_y == coordinates_y[1])):
        if(min_y > 0):
                area += abs(max_x-min_x)*abs(min_y)
                area += abs(coordinates_x[1] - coordinates_x[0]) * abs(coordinates_y[0] - coordinates_y[1])/2
                area += abs(coordinates_x[1] - coordinates_x[3]) * abs(coordinates_y[1] - coordinates_y[3]) / 2
                
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[2]*coordinates_y[1] + coordinates_x[1]*coordinates_y[3] + coordinates_x[3]*coordinates_y[2] - coordinates_y[2]*coordinates_x[1] - coordinates_y[1]*coordinates_x[3] - coordinates_y[3]*coordinates_x[2]) / 2
        else:
                area += abs((coordinates_x[3] - coordinates_x[0])*abs(coordinates_y[0] - coordinates_y[3]))/2
       
                area += (coordinates_x[3] - coordinates_x[0]) * abs(max_y)


if((max_x == coordinates_x[3] and coordinates_x[1] <= coordinates_x[2] <= coordinates_x[0]) and (min_y == coordinates_y[0] or min_y == coordinates_y[3])):
        if(min_y > 0):
                area += abs(max_x-min_x)*abs(min_y)
                area += abs(coordinates_x[0] - coordinates_x[3]) * abs(coordinates_y[3] - coordinates_y[0])/2
                area += abs(coordinates_x[0] - coordinates_x[2]) * abs(coordinates_y[0] - coordinates_y[2]) / 2
                #1/2 |x1.y2+x2.y3+x3.y1−(y1.x2+y2.x3+y3.x1)|
                area += abs(coordinates_x[1]*coordinates_y[0] + coordinates_x[0]*coordinates_y[2] + coordinates_x[2]*coordinates_y[1] - coordinates_y[1]*coordinates_x[0] - coordinates_y[0]*coordinates_x[2] - coordinates_y[2]*coordinates_x[1]) / 2
        else:
                area += abs((coordinates_x[2] - coordinates_x[3])*abs(coordinates_y[3] - coordinates_y[2]))/2
       
                area += (coordinates_x[2] - coordinates_x[3]) * abs(max_y)



print(f"%.2f" %area) 

"""[(12.5,11.3), (2.0,12.0), (18.7,16.2), (12.5,7.0)]"""
