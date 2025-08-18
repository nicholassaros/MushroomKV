#include "ResponseBuilder.h"

Response::Response(RequestType requestType, std::string data)
    : requestType(requestType), data(data){
};

Response ResponseBuilder::build(RequestType requestType, std::string data) {
    return Response(requestType, data);
};