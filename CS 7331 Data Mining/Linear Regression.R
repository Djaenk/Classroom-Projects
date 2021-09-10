library(MASS)
myData <- Cars93

str(myData)
summary(myData)
myData <- na.omit(myData)
myData <- myData[, sapply(myData, class) != "factor"]

train <- myData[1:60,]
test <- myData[-(1:60),]

model <- lm(Horsepower ~ ., data = train)
prediction <- predict(model, test)
MSE <- mean((prediction - test$Horsepower)^2)

model2 <- lm(Horsepower ~ EngineSize + RPM + Wheelbase + Weight, data = train)
prediction2 <- predict(model2, test)
MSE2 <- mean((prediction2 - test$Horsepower)^2)

