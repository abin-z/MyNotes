package config;

import org.springframework.context.annotation.Import;

/**
 * @Author Abin
 * @Date 2022/06/13
 * @Description:
 */
@org.springframework.context.annotation.Configuration
@Import(DataSource.class)
public class Configuration {

}
