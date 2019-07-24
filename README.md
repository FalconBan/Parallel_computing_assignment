# Parallel_computing_assignment
# Build Command

g++ -I"." -c linked_list.cpp -o linked_list.o
g++ -I"." -c linked_list_single_mutex.cpp -o linked_list_single_mutex.o
g++ -I"." -c linked_list_rwlock.cpp -o linked_list_rwlock.o
g++ -std=c++1y -I"." -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Main.d" -MT"Main.o" -o "Main.o" "Main.cpp"
g++ Main.o linked_list.o linked_list_single_mutex.o linked_list_rwlock.o -lpthread -o Test
