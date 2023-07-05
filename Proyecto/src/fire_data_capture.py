import serial
import csv

# Configure the serial connection
arduino_port = '/dev/ttyACM0'
baud_rate = 9600  # Set the baud rate to match your Arduino

# Open the serial connection
ser = serial.Serial(arduino_port, baud_rate)

# Create the CSV file and write the header
csv_file = open('Fire.csv', 'w', newline='')
csv_writer = csv.writer(csv_file)
csv_writer.writerow(['Red', 'Green', 'Blue'])

# Set the desired number of data sets to capture
num_data_sets = 4000

# Read and process data from Arduino
data_sets_captured = 0
while data_sets_captured < num_data_sets:
    # Read a line of data from the Arduino
    data = ser.readline().decode().strip()
    #print(data)

    # Split the line into three values (Red, Green, Blue)
    values = data.split(',')

    # Check if the data is valid (contains three values)
    if len(values) == 3:
        # Write the data to the CSV file
        csv_writer.writerow(values)
        csv_file.flush()  # Ensure data is written immediately

        data_sets_captured += 1
    print(data_sets_captured)

# Close the serial connection and CSV file
ser.close()
csv_file.close()
