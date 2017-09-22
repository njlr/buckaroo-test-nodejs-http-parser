#include <stdlib.h>
#include <http_parser.h>
#include <gtest/gtest.h>

static http_parser_settings settings_null ={
  .on_message_begin = 0,
  .on_header_field = 0,
  .on_header_value = 0,
  .on_url = 0,
  .on_status = 0,
  .on_body = 0,
  .on_headers_complete = 0,
  .on_message_complete = 0,
  .on_chunk_header = 0,
  .on_chunk_complete = 0
};

TEST(httpparser, basics) {
  http_parser parser;
  http_parser_init(&parser, HTTP_REQUEST);
  size_t parsed;
  const char* buf = "GET / HTTP/1.1\r\n";
  parsed = http_parser_execute(&parser, &settings_null, buf, strlen(buf));
  assert(parsed == strlen(buf));

  buf = "Content-Length: 0\r\nContent-Length: 1\r\n\r\n";
  size_t buflen = strlen(buf);

  parsed = http_parser_execute(&parser, &settings_null, buf, buflen);
  ASSERT_TRUE(parsed != buflen);
  assert(HTTP_PARSER_ERRNO(&parser) == HPE_UNEXPECTED_CONTENT_LENGTH);
}
