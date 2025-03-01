-- Таблица для хранения информации о пользователях
CREATE TABLE IF NOT EXISTS users (
                                     id UUID PRIMARY KEY,
                                     username TEXT,
                                     first_name TEXT,
                                     last_name TEXT,
                                     profile_photo_url TEXT,
                                     key_version int,
                                     created_at TIMESTAMP
) WITH default_time_to_live = 0;