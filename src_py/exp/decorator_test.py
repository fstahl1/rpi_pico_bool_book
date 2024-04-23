



def decor(fun):
    def wrapper():
        return fun() + 3
    return wrapper

def foo():
    return 2

decorated_fun = decor(foo)
print(decorated_fun())



# bar = decor(foo)

# test = bar(1)



# # Define a decorator function
# def my_decorator(func):
#     def wrapper():
#         print("Something is happening before the function is called.")
#         func()  # Call the original function
#         print("Something is happening after the function is called.")
#     return wrapper

# # Define a function and apply the decorator to it
# @my_decorator
# def say_hello():
#     print("Hello!")

# # Call the decorated function
# say_hello()
