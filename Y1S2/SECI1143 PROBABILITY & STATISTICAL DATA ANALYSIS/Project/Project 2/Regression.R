# Load necessary libraries
library(readxl)

# Define the file path
file_path <- "C:/Users/User/Downloads/qs-world-rankings-2025.xlsx"

# Load the dataset
qs_data <- read_excel(file_path)

# Convert QS Overall Score to numeric if needed
qs_data$`QS Overall Score` <- as.numeric(qs_data$`QS Overall Score`)

# Function to calculate t-value
calculate_t_value <- function(coeff_estimate, std_error) {
  t_value <- coeff_estimate / std_error
  return(t_value)
}

# Function to calculate critical t-value with higher precision
calculate_critical_t_value <- function(alpha, df) {
  critical_t_value <- qt(1 - alpha/2, df = df)  # Two-tailed test
  return(critical_t_value)
}

# Regression Test function
regressionTesting <- function(dependent_var_name, independent_var_name, dependent_label, independent_label, plot_title, alpha = 0.05) {
  x <- qs_data[[independent_var_name]]
  y <- qs_data[[dependent_var_name]]
  
  if (length(x) > 0 && length(y) > 0) {
    model <- lm(y ~ x)
    summary_model <- summary(model)
    
    print(paste("Regression:", dependent_label, "vs", independent_label))
    print(summary_model)
    
    plot(x, y, main = plot_title, xlab = independent_label, ylab = dependent_label, xlim = c(0, 100), ylim = c(0, 100))
    abline(model, col = "blue")
    
    b1 <- summary_model$coefficients[2, "Estimate"]
    sb1 <- summary_model$coefficients[2, "Std. Error"]
    df <- summary_model$df[2]
    
    t_value <- calculate_t_value(b1, sb1)
    
    print("T-test Results:")
    print(paste("Test statistic (t):", sprintf("%.3f", t_value)))
    print(paste("Degrees of freedom:", sprintf("%d", df)))
    
    critical_t <- calculate_critical_t_value(alpha, df)
    print(paste("Critical t-value (alpha =", alpha, "):", format(critical_t, nsmall = 10)))
  } else {
    cat("Error: No valid data points for regression.\n")
  }
}

# Perform regression tests and plot for each pair
par(mfrow = c(1, 3))

# 3.3.1 Academic Reputation vs Employer Reputation
print("3.3.1 Academic Reputation vs Employer Reputation")
regressionTesting("Employer Reputation", "Academic Reputation", "Employer Reputation", "Academic Reputation", "Academic Reputation vs Employer Reputation")

# 3.3.2 Academic Reputation vs QS Overall Score
print("3.3.2 Academic Reputation vs QS Overall Score")
regressionTesting("Academic Reputation", "QS Overall Score", "Academic Reputation", "QS Overall Score", "Academic Reputation vs QS Overall Score")

# 3.3.3 Employer Reputation vs QS Overall Score
print("3.3.3 Employer Reputation vs QS Overall Score")
regressionTesting("Employer Reputation", "QS Overall Score", "Employer Reputation", "QS Overall Score", "Employer Reputation vs QS Overall Score")

