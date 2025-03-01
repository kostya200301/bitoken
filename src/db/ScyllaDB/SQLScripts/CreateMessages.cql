CREATE TABLE IF NOT EXISTS messages (
                                        id UUID,
                                        chat_id UUID,
                                        sender_id UUID,
                                        data TEXT,
                                        sender_key_version INT,
                                        date_time TIMESTAMP,
                                        PRIMARY KEY ((chat_id), date_time, id)
) WITH default_time_to_live = 0;
