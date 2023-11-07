import cv2
import numpy as np

# Initialize video capture from a file or camera
cap = cv2.VideoCapture(-1)  # Replace with your video source

# Define initial variables for tracking
ball_position = None
ball_velocity = None
time_step = 0.1  # Time step for predicting the next position

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Preprocess the frame
    # You may need to resize, denoise, and adjust colors here

    # Object detection (for simplicity, we'll use color-based detection)
    lower_color = np.array([0, 100, 100])
    upper_color = np.array([20, 255, 255])
    frame_hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(frame_hsv, lower_color, upper_color)
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if contours:
        # Find the largest contour (assumes it's the ball)
        largest_contour = max(contours, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(largest_contour)
        ball_position = (int(x), int(y))

        # Object tracking (for simplicity, we'll just use the position as velocity)
        if ball_velocity is not None:
            ball_velocity = (ball_position[0] - prev_position[0], ball_position[1] - prev_position[1])
        prev_position = ball_position

        # Predict the next position of the ball
        if ball_velocity is not None:
            next_position = (
                int(ball_position[0] + ball_velocity[0] * time_step),
                int(ball_position[1] + ball_velocity[1] * time_step)
            )

            # Draw the ball and predicted path on the frame
            cv2.circle(frame, ball_position, int(radius), (0, 255, 0), 2)
            cv2.line(frame, ball_position, next_position, (0, 0, 255), 2)

    # Display the frame with tracking information
    cv2.imshow('Ball Tracking', frame)

    if cv2.waitKey(1) & 0xFF == 27:  # Press 'Esc' to exit
        break

# Release the video capture and close the OpenCV windows
cap.release()
cv2.destroyAllWindows()
