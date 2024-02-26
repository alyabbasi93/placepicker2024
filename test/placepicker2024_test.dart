import 'package:flutter_test/flutter_test.dart';
import 'package:placepicker2024/placepicker2024.dart';
import 'package:placepicker2024/placepicker2024_platform_interface.dart';
import 'package:placepicker2024/placepicker2024_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockPlacepicker2024Platform
    with MockPlatformInterfaceMixin
    implements Placepicker2024Platform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final Placepicker2024Platform initialPlatform = Placepicker2024Platform.instance;

  test('$MethodChannelPlacepicker2024 is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelPlacepicker2024>());
  });

  test('getPlatformVersion', () async {
    Placepicker2024 placepicker2024Plugin = Placepicker2024();
    MockPlacepicker2024Platform fakePlatform = MockPlacepicker2024Platform();
    Placepicker2024Platform.instance = fakePlatform;

    expect(await placepicker2024Plugin.getPlatformVersion(), '42');
  });
}
