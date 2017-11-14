ROS_COMM_PATH := deps/ros_comm
ROS_CPP_PATH := ${ROS_COMM_PATH}/clients/roscpp
ROS_CPP_SRC_PATH := ${ROS_CPP_PATH}/src/libros

ROS_CPP_SRC := ${ROS_CPP_SRC_PATH}/src/serialization.cpp \
	callback_queue.cpp \
	common.cpp \
	connection.cpp \
	connection_manager.cpp \
	file_log.cpp \
	init.cpp \
	internal_timer_manager.cpp \
	intraprocess_publisher_link.cpp \
	intraprocess_subscriber_link.cpp \
	io.cpp \
	master.cpp \
	message_deserializer.cpp \
	names.cpp \
	network.cpp \
	node_handle.cpp \
	param.cpp \
	poll_manager.cpp \
	poll_set.cpp \
	publication.cpp \
	publisher.cpp \
	publisher_link.cpp \
	rosout_appender.cpp \
	service_client.cpp \
	service_client_link.cpp \
	service.cpp \
	service_manager.cpp \
	service_publication.cpp \
	service_server.cpp \
	service_server_link.cpp \
	single_subscriber_publisher.cpp \
	spinner.cpp \
	statistics.cpp \
	steady_timer.cpp \
	subscriber.cpp \
	subscriber_link.cpp \
	subscription.cpp \
	subscription_queue.cpp \
	this_node.cpp \
	timer.cpp \
	topic.cpp \
	topic_manager.cpp \
	transport \
	transport_publisher_link.cpp \
	transport_subscriber_link.cpp \
	wall_timer.cpp \
	xmlrpc_manager.cpp \

ROS_CPP_OBJ := $(ROS_CPP_SRC:.cpp=.o)

ROS_CPP_LIB := lib/libros_cpp.a

${ROS_CPP_LIB}: ${ROS_CPP_OBJ}
	@echo AR $@
	@ar rcs $@ $^

ALL_OBJ := ${ALL_OBJ} ${ROS_CPP_OBJ}
ALL_LIB := ${ALL_LIB} ${ROS_CPP_LIB}

G_CXXFLAGS := ${G_CXXFLAGS} -I${ROS_CPP_PATH}/include -I${ROS_COMM_PATH}/tools/rosconsole/include



