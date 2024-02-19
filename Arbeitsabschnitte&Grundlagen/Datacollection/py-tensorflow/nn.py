import tensorflow as tf
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten
from tensorflow.keras.utils import to_categorical

from mnist import MNIST
import numpy as np

# Initialize MNIST loader
mndata = MNIST('/path/to/your/dataset')
trimages, trlabels = mndata.load_training()
teimages, telabels = mndata.load_testing()


# Convert to NumPy arrays and normalize the images
trimages = np.array(trimages).reshape(-1, 28, 28, 1).astype('float32') / 255.0  # Reshape for CNN and normalize
trlabels = np.array(trlabels).astype('int32')
trlabels = tf.keras.utils.to_categorical(trlabels, num_classes=10)# Convert to one-hot encoding if necessary

teimages = np.array(teimages).reshape(-1, 28, 28, 1).astype('float32') / 255.0  # Reshape for CNN and normalize
telabels = np.array(telabels).astype('int32')
telabels = tf.keras.utils.to_categorical(telabels, num_classes=10)# Convert to one-hot encoding if necessary

# Create tf.data.Dataset
train_dataset = tf.data.Dataset.from_tensor_slices((trimages, trlabels))
test_dataset = tf.data.Dataset.from_tensor_slices((teimages, telabels))

# Shuffle and batch the dataset
#batch_size = 128
#train_dataset = train_dataset.shuffle(buffer_size=1024).batch(batch_size)

# Build the model with sigmoid activations in the hidden layers
model = Sequential([
    Flatten(input_shape=(784,)),
    Dense(32, activation='sigmoid'), # Using sigmoid activation
    Dense(16, activation='sigmoid'), # Using sigmoid activation
    Dense(10, activation='sigmoid')
])

# Compile the model
model.compile(optimizer='adam',
              loss='categorical_crossentropy',
              metrics=['accuracy'])

# Train the model
model.fit(train_dataset, epochs=1)

# Evaluate the model
test_loss, test_acc = model.evaluate(test_dataset)

print('Test accuracy:', test_acc)
