import sys
sys.path.append('/usr/local/lib/python2.7/site-packages')
import numpy as np
import math
import cv2

object_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
inner_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')
font = cv2.FONT_HERSHEY_SIMPLEX

class Object_Detector:
    def __init__(self, file, classifier, thresh=.45):
        self.file = file
        self.image = cv2.imread(file)
        self.classifier = classifier
        self.thresh = thresh

    def is_found(self, rec, img):
        print(rec / img)
        if rec / img >= self.thresh:
            print("Found")
            x, y = self.find_image_center()
            cv2.putText(self.image, "FOUND", (x, y), font, 1,(0,255,0),2)
        else:
            print(self.image.shape)

    def find_image_center(self):
        x, y, z = self.image.shape
        return (int(y/2), int(x/2))

    def find_perspective(self):
        x, y, z = self.image.shape
        return (int(y/2), int(x))

    def draw_dot(self, img, point, circ_size):
        x, y = point
        cv2.circle(img, (x, y), circ_size, (255,0,0), -1)

    def find_area(self, b, h):
        return b * h

    def find_obj(self):
        img = self.image
        (center_x, center_y) = self.find_perspective()
        img_w, img_h, img_c = self.image.shape
        img_size = self.find_area(img_w, img_h)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        objects = self.classifier.detectMultiScale(gray, 1.3, 5)
        # print(objects)
        (rec_center_x, rec_center_y) = (0, 0)
        rec_area = 0
        for (x,y,w,h) in objects:
            box = cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2) # Originally had "img ="
            rec_area = self.find_area(w, h)
            (rec_center_x, rec_center_y) = self.find_rectangle_center((x, y, w, h))
            # print (rec_center_x, rec_center_y)
            roi_gray = gray[y:y+h, x:x+w]
            roi_color = img[y:y+h, x:x+w]
            # inners = inner_cascade.detectMultiScale(roi_gray)
            # for (ex,ey,ew,eh) in inners:
            #     cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)

        object_centers = [(x + (w / 2), y + (h / 2)) for (x, y , w, h) in objects]
        self.draw_dot(self.image, (center_x, center_y), 10)
        self.draw_dot(self.image, (rec_center_x, rec_center_y), 10)

        ang = self.angle_between_points((center_x, center_y), (rec_center_x, rec_center_y)) 
        print(ang)
        cv2.line(self.image, (center_x, 0), (center_x, center_y), (0,0,255), 3, -1)
        cv2.putText(self.image, str(int(ang)) + ' degrees', (center_x + 50, center_y - 50), font, 1,(0,0,255),2)

        self.is_found(rec_area, img_size)


        cv2.imshow('img', self.image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    def find_rectangle_center(self, rec):
        x, y, w, h = rec
        center_x = x + w / 2
        center_y = y + h / 2
        return (int(center_x), int(center_y))

    def find_degrees(self, x, y):
        return math.degrees(math.atan(y/x))


    # Our use case implies p1 is the center of image and p2 is the center of object.
    def angle_between_points(self, p1, p2):
        p1_x, p1_y = p1
        p2_x, p2_y = p2
        # print("p1 is ", p1)
        # print("p2 is ", p2)
        flip = False

        if (p2_x < p1_x):
            flip = True
 
        delta_y = p1_y - p2_y
        # delta_x = temp_x1 - temp_x0
        delta_x = p2_x - p1_x

        cv2.line(self.image, p1, p2, (0,0,255), 3, -1)

        # print(delta_x, delta_y)

        deg = self.find_degrees(delta_x, delta_y)

        # If flip is true, this means we need to transform our angle to be negative.
        if flip:
            deg = 90 - (180 + deg)
        else:
            deg = 90 - deg

        return deg



finder = Object_Detector('lab.jpg', object_cascade)
# finder = Object_Detector('croissant.jpg', object_cascade)
# finder = Object_Detector('face_gradient.png', object_cascade)
# finder = Object_Detector('zoom.jpg', object_cascade)

finder.find_obj()
c1 = Object_Detector('curry1.jpg', object_cascade)
c1.find_obj()
c2 = Object_Detector('curry2.jpg', object_cascade, .42)
c2.find_obj()
