"""
[0] -- x1
[1] -- x2
[2] -- target val (aka class)
"""
data_set   = [[1, 1, 1],
              [3, 1, 1],
              [1, 3, -1],
              [3, 3, -1]]

data_set2   = [[1, 1, 1],
               [1, -1, -1],
               [-1, -1, 1],
               [-1, 1, -1]]

# init defaults
ALPHA       = 1
beta0       = -1
beta_entry1 = 1
beta_entry2 = -1


def calc_check(classifier, x1_val, x2_val):
    return classifier * (beta0 + beta_entry1*x1_val + beta_entry2*x2_val)


# Select for 2nd exercise
#data_set = data_set2

errors = 1
total_updates = 0
steps_performed = 0;
while errors > 0:
    steps_performed += 1
    errors = 0
    for i in range(0, len(data_set)):
        x1_val = data_set[i][0]
        x2_val = data_set[i][1]
        y_val  = data_set[i][2]

        print("x_val: (" + str(x1_val) + ", " + str(x2_val) + ")")
        print("y_val: " + str(y_val))

        result = calc_check(y_val, x1_val, x2_val)
        if result <= 0:
            errors += 1
            total_updates += 1
            print("result of calc_check is <= 0: " + str(result))
            print("errors++, need to update the hyperplane!")
            beta0 = beta0 + ALPHA * y_val
            beta_entry1 = beta_entry1 + ALPHA * y_val * x1_val
            beta_entry2 = beta_entry2 + ALPHA * y_val * x2_val
            print("new beta0: " + str(beta0))
            print("new beta: (" + str(beta_entry1) + ", " + str(beta_entry2) + ")")

print("FINAL HYPERPLANE: " + str(beta0) + " + " + str(beta_entry1) + " * x1 + " + str(beta_entry2) + " * x2")
print("NUM OF UPDATES: " + str(total_updates));

