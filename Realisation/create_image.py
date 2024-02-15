import numpy as np
import matplotlib.pyplot as plt
from PIL import Image #Pillow

width, height = 28, 28
dpi = 100

fig, ax = plt.subplots(figsize=(width/dpi, height/dpi), dpi=dpi)
ax.set_xlim([0, width])
ax.set_ylim([height, 0])
ax.axis('off')

drawing = False
image_data = np.zeros((height, width))

def on_draw(event):
    global drawing
    if drawing:
        x, y = int(event.xdata), int(event.ydata)
        if 0 <= x < width and 0 <= y < height:
            image_data[y, x] = 255  #
            ax.clear()
            ax.imshow(image_data, cmap='gray', vmin=0, vmax=255)
            plt.draw()

def on_click(event):
    global drawing
    if event.button == 1:
        drawing = True
    elif event.button == 3:
        drawing = False

def on_release(event):
    global drawing
    drawing = False

def on_close(event):
    im = Image.fromarray(image_data)
    im = im.convert('L')
    im.save('drawing.jpg', 'JPEG')
    print("Image saved as 'drawing.jpg'")

fig.canvas.mpl_connect('motion_notify_event', on_draw)
fig.canvas.mpl_connect('button_press_event', on_click)
fig.canvas.mpl_connect('button_release_event', on_release)
fig.canvas.mpl_connect('close_event', on_close)

plt.show()
