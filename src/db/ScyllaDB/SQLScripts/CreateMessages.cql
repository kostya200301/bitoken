CREATE TABLE IF NOT EXISTS messages (
                                        chat_id UUID,
                                        sender_id UUID,
                                        id TIMEUUID,
                                        data TEXT,
                                        sender_key_version INT,
                                        date_time TIMESTAMP,
                                        PRIMARY KEY ((chat_id), id)
) WITH CLUSTERING ORDER BY (id DESC);
